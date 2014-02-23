/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <base/tl/sorted_array.h>

#include <base/math.h>

#include <engine/config.h>
#include <engine/shared/config.h>
#include <engine/graphics.h>

#include <game/collision.h>
#include <game/client/gameclient.h>
#include <game/client/component.h>
#include <game/client/components/chat.h>
#include <game/client/components/menus.h>
#include <game/client/components/scoreboard.h>

#include "controls.h"

CControls::CControls() : auto_hit(false), hit_interval(0), 
	auto_hook(false), auto_hook_type(0), aimbot(-1), aimbot_predict(0.f), aimbot_predict_dist(0.012f /* 1 / HookFireSpeed */), aimbot_smooth(0)
{
	mem_zero(&m_LastData, sizeof(m_LastData));
}

void CControls::OnReset()
{
	m_LastData.m_Direction = 0;
	m_LastData.m_Hook = 0;
	// simulate releasing the fire button
	if((m_LastData.m_Fire&1) != 0)
		m_LastData.m_Fire++;
	m_LastData.m_Fire &= INPUT_STATE_MASK;
	m_LastData.m_Jump = 0;
	m_InputData = m_LastData;

	m_InputDirectionLeft = 0;
	m_InputDirectionRight = 0;
}

void CControls::OnRelease()
{
	//OnReset();
}

void CControls::OnPlayerDeath()
{
	m_LastData.m_WantedWeapon = m_InputData.m_WantedWeapon = 0;
}

static void ConKeyInputState(IConsole::IResult *pResult, void *pUserData)
{
	((int *)pUserData)[0] = pResult->GetInteger(0);
}

static void ConKeyInputCounter(IConsole::IResult *pResult, void *pUserData)
{
	int *v = (int *)pUserData;
	if(((*v)&1) != pResult->GetInteger(0))
		(*v)++;
	*v &= INPUT_STATE_MASK;
}

struct CInputSet
{
	CControls *m_pControls;
	int *m_pVariable;
	int m_Value;
};

static void ConKeyInputSet(IConsole::IResult *pResult, void *pUserData)
{
	CInputSet *pSet = (CInputSet *)pUserData;
	if(pResult->GetInteger(0))
		*pSet->m_pVariable = pSet->m_Value;
}

static void ConKeyInputNextPrevWeapon(IConsole::IResult *pResult, void *pUserData)
{
	CInputSet *pSet = (CInputSet *)pUserData;
	ConKeyInputCounter(pResult, pSet->m_pVariable);
	pSet->m_pControls->m_InputData.m_WantedWeapon = 0;
}

static void ConMousePos(IConsole::IResult *pResult, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	pSelf->m_MousePos = vec2(pResult->GetFloat(0), pResult->GetFloat(1));
	//pSelf->m_TargetPos = pSelf->m_MousePos;
	pSelf->OnRender();
}

static void ConMouseAngle(IConsole::IResult *pResult, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	const float pi = 3.1415926535f;
	const float dist = 200.f;
	pSelf->m_MousePos = vec2(cosf(pResult->GetFloat(0) * pi / 180.f) * dist, sinf(pResult->GetFloat(0) * pi / 180.f) * dist);
	//pSelf->m_TargetPos = pSelf->m_MousePos;
	pSelf->OnRender();
}

struct CMouseGet
{
	vec2 *m_MousePos;
	vec2 *m_TargetPos;
	IConsole *m_pConsole;
};

static void ConMouseGet(IConsole::IResult *pResult, void *pUserData)
{
	CMouseGet *pSelf = (CMouseGet *)pUserData;
	float x = pSelf->m_MousePos->x, y = pSelf->m_MousePos->y;
	float angle = atan2(y, x) / pi * 180.f;
	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "a: %.4f  x: %.4f  y: %.4f  tx: %.4f  ty: %.4f", angle, x, y,
		pSelf->m_TargetPos->x, pSelf->m_TargetPos->y);
	pSelf->m_pConsole->Print(IConsole::OUTPUT_LEVEL_STANDARD, "binds", aBuf);

}

static void ConAutoHit(IConsole::IResult *pResult, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	pSelf->auto_hit = !!pResult->GetInteger(0);
	if(!pSelf->auto_hit)
	{
		if(pSelf->m_InputData.m_Fire & 1)
			pSelf->m_InputData.m_Fire = (pSelf->m_InputData.m_Fire + 1) & INPUT_STATE_MASK;
	}
	pSelf->hit_interval = int64(pResult->GetInteger(1)) * time_freq() / 1000LL;
}

static void ConAutoHook(IConsole::IResult *pResult, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	pSelf->auto_hook = !!pResult->GetInteger(0);
	if(!pSelf->auto_hook)
		pSelf->m_InputData.m_Hook = 0;
	pSelf->auto_hook_type = pResult->GetInteger(1);
}

static void ConAimbotLock(IConsole::IResult *pResult, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	bool online = pResult->GetInteger(0);
	pSelf->aimbot = online ? pResult->GetInteger(1) : (-1);
}

struct CAimbot
{
	CGameClient *pClient;
	CControls *pControls;
};

static void ConAimbot(IConsole::IResult *pResult, void *pUserData)
{
	CAimbot *pSelf = (CAimbot *)pUserData;
	if(!pResult->GetInteger(0))
	{
		pSelf->pControls->aimbot = (-1);
		return;
	}
	else if(pSelf->pControls->aimbot != -1)
		return;
	if(!pSelf->pClient->IsDDRaceServer())
		return;
	
	int64 mindist = 1000000000LL;
	int id = -1;
	
	/*
	int xl = pSelf->pClient->m_Snap.m_aCharacters[pSelf->pClient->m_Snap.m_LocalClientID].m_Cur.m_X;
	int yl = pSelf->pClient->m_Snap.m_aCharacters[pSelf->pClient->m_Snap.m_LocalClientID].m_Cur.m_Y;
	
	xl += int(pSelf->pControls->m_MousePos.x);
	yl += int(pSelf->pControls->m_MousePos.y);
	*/
	int xl = int(pSelf->pControls->m_TargetPos.x);
	int yl = int(pSelf->pControls->m_TargetPos.y);
	
	int localid = pSelf->pClient->m_Snap.m_LocalClientID;
	
	if(pSelf->pClient->m_Snap.m_SpecInfo.m_Active && pSelf->pClient->m_Snap.m_SpecInfo.m_UsePosition)
		localid = pSelf->pClient->m_Snap.m_SpecInfo.m_SpectatorID;
	
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(!pSelf->pClient->m_Snap.m_aCharacters[i].m_Active || i == localid)
			continue;
		int x = pSelf->pClient->m_Snap.m_aCharacters[i].m_Cur.m_X;
		int y = pSelf->pClient->m_Snap.m_aCharacters[i].m_Cur.m_Y;
		int64 dist = (x-xl)*(x-xl) + (y-yl)*(y-yl);
		if(dist < mindist)
		{
			mindist = dist;
			id = i;
		}
	}
	
	pSelf->pControls->aimbot = id;
	pSelf->pControls->Aim();
}
static void ConAimbotPredict(IConsole::IResult *pResult, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	pSelf->aimbot_predict = pResult->GetFloat(0);
}
static void ConAimbotPredictDistance(IConsole::IResult *pResult, void *pUserData)
{
    CControls *pSelf = (CControls *)pUserData;
    pSelf->aimbot_predict_dist = pResult->GetFloat(0);
}

static void ConfigSaveCallback(class IConfig *pConfig, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	
	char buf[128];
	str_format(buf, sizeof(buf), "aimbot_predict %f", pSelf->aimbot_predict);
	pConfig->WriteLine(buf);
	str_format(buf, sizeof(buf), "aimbot_dist %f", pSelf->aimbot_predict_dist);
	pConfig->WriteLine(buf);
	str_format(buf, sizeof(buf), "aimbot_smooth %d", pSelf->aimbot_smooth);
	pConfig->WriteLine(buf);
}


void CControls::OnConsoleInit()
{
	IConfig *pConfig = Kernel()->RequestInterface<IConfig>();
	if(pConfig)
		pConfig->RegisterCallback(ConfigSaveCallback, this);
	
	// game commands
	Console()->Register("+left", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputDirectionLeft, "Move left");
	Console()->Register("+right", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputDirectionRight, "Move right");
	Console()->Register("+jump", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputData.m_Jump, "Jump");
	Console()->Register("+hook", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputData.m_Hook, "Hook");
	Console()->Register("+fire", "", CFGFLAG_CLIENT, ConKeyInputCounter, &m_InputData.m_Fire, "Fire");
	Console()->Register("+showhookcoll", "", CFGFLAG_CLIENT, ConKeyInputState, &m_ShowHookColl, "Show Hook Collision");

	Console()->Register("mouse", "ff", CFGFLAG_CLIENT, ConMousePos, this, "Set mouse position");
	Console()->Register("mouse_angle", "f", CFGFLAG_CLIENT, ConMouseAngle, this, "Set mouse angle in degree");
	{ static CMouseGet s_Set = {&m_MousePos, &m_TargetPos, Console()}; Console()->Register("mouse_get", "", CFGFLAG_CLIENT, ConMouseGet, (void *)&s_Set, "Get mouse position and angle"); }
	
	Console()->Register("autohit", "ii", CFGFLAG_CLIENT, ConAutoHit, this, "Spam-click fire");
	Console()->Register("+autohit", "i", CFGFLAG_CLIENT, ConAutoHit, this, "Spam-click fire");
	Console()->Register("autohook", "i?i", CFGFLAG_CLIENT, ConAutoHook, this, "Auto hook");
	Console()->Register("+autohook", "?i", CFGFLAG_CLIENT, ConAutoHook, this, "Auto hook");
	Console()->Register("+aimbot", "i", CFGFLAG_CLIENT, ConAimbotLock, this, "Aimbot lock to player");
	{ static CAimbot s_Set = {m_pClient, this}; Console()->Register("+aimbotnear", "", CFGFLAG_CLIENT, ConAimbot, (void *)&s_Set, "Aimbot lock to the nearest player"); }
    Console()->Register("aimbot_predict", "f", CFGFLAG_CLIENT, ConAimbotPredict, this, "Set aimbot prediction");
    Console()->Register("aimbot_dist", "f", CFGFLAG_CLIENT, ConAimbotPredictDistance, this, "Set aimbot prediction distance multiplier");
    
    Console()->Register("aimbot_smooth", "i", CFGFLAG_CLIENT, ([](IConsole::IResult *pResult, void *pUserData)
    {
		((CControls *)pUserData)->aimbot_smooth = pResult->GetInteger(0);
    }), this, "Toggle smoother visual aim (0=on input send, 1=on render, 2=stealth");
    
	{ static CInputSet s_Set = {this, &m_InputData.m_WantedWeapon, 1}; Console()->Register("+weapon1", "", CFGFLAG_CLIENT, ConKeyInputSet, (void *)&s_Set, "Switch to hammer"); }
	{ static CInputSet s_Set = {this, &m_InputData.m_WantedWeapon, 2}; Console()->Register("+weapon2", "", CFGFLAG_CLIENT, ConKeyInputSet, (void *)&s_Set, "Switch to gun"); }
	{ static CInputSet s_Set = {this, &m_InputData.m_WantedWeapon, 3}; Console()->Register("+weapon3", "", CFGFLAG_CLIENT, ConKeyInputSet, (void *)&s_Set, "Switch to shotgun"); }
	{ static CInputSet s_Set = {this, &m_InputData.m_WantedWeapon, 4}; Console()->Register("+weapon4", "", CFGFLAG_CLIENT, ConKeyInputSet, (void *)&s_Set, "Switch to grenade"); }
	{ static CInputSet s_Set = {this, &m_InputData.m_WantedWeapon, 5}; Console()->Register("+weapon5", "", CFGFLAG_CLIENT, ConKeyInputSet, (void *)&s_Set, "Switch to rifle"); }

	{ static CInputSet s_Set = {this, &m_InputData.m_NextWeapon, 0}; Console()->Register("+nextweapon", "", CFGFLAG_CLIENT, ConKeyInputNextPrevWeapon, (void *)&s_Set, "Switch to next weapon"); }
	{ static CInputSet s_Set = {this, &m_InputData.m_PrevWeapon, 0}; Console()->Register("+prevweapon", "", CFGFLAG_CLIENT, ConKeyInputNextPrevWeapon, (void *)&s_Set, "Switch to previous weapon"); }
}

void CControls::OnMessage(int Msg, void *pRawMsg)
{
	if(Msg == NETMSGTYPE_SV_WEAPONPICKUP)
	{
		CNetMsg_Sv_WeaponPickup *pMsg = (CNetMsg_Sv_WeaponPickup *)pRawMsg;
		if(g_Config.m_ClAutoswitchWeapons)
			m_InputData.m_WantedWeapon = pMsg->m_Weapon+1;
	}
}

int CControls::SnapInput(int *pData)
{
	static int64 LastSendTime = 0;
	bool Send = false;

	static int64 last_hit_time = 0;
	//static int64 last_hook_time = 0;

	int64 time = time_get();
	

	// update player state
	if(m_pClient->m_pChat->IsActive())
		m_InputData.m_PlayerFlags = PLAYERFLAG_CHATTING;
	else if(m_pClient->m_pMenus->IsActive() || !(static_cast<IEngineGraphics *>(Graphics())->WindowActive()))
		m_InputData.m_PlayerFlags = PLAYERFLAG_IN_MENU;
	else
		m_InputData.m_PlayerFlags = PLAYERFLAG_PLAYING;

	if(m_pClient->m_pScoreboard->Active())
		m_InputData.m_PlayerFlags |= PLAYERFLAG_SCOREBOARD;

	if (m_ShowHookColl || (auto_hook && auto_hook_type&4))
		m_InputData.m_PlayerFlags |= PLAYERFLAG_AIM;

	if(m_LastData.m_PlayerFlags != m_InputData.m_PlayerFlags)
		Send = true;

	m_LastData.m_PlayerFlags = m_InputData.m_PlayerFlags;

	if(auto_hit && last_hit_time + hit_interval < time)
	{
		m_InputData.m_Fire = (m_InputData.m_Fire + 1) & INPUT_STATE_MASK;
		last_hit_time = time;
		Send = true;
	}
	if(auto_hook) // rehook
	{
		AutoHook();
	}
	if(aimbot_smooth == 0 || aimbot_smooth == 1)
		Aim();
	else 
	{
		if((aimbot_smooth&2 && m_InputData.m_Fire != m_LastData.m_Fire && m_InputData.m_Fire&1) ||
			(aimbot_smooth&4 && ((!m_LastData.m_Hook && m_InputData.m_Hook) || auto_hook)))
				Aim();
	}


	// we freeze the input if menu is activated
	if(m_pClient->m_pMenus->IsActive())
	{
		OnReset();

		mem_copy(pData, &m_InputData, sizeof(m_InputData));

		// send once a second just to be sure
		if(time > LastSendTime + time_freq())
			Send = true;
	}
	else
	{
		m_InputData.m_TargetX = round(m_MousePos.x);
		m_InputData.m_TargetY = round(m_MousePos.y);


		// set direction
		m_InputData.m_Direction = 0;
		if(m_InputDirectionLeft && !m_InputDirectionRight)
			m_InputData.m_Direction = -1;
		else if(!m_InputDirectionLeft && m_InputDirectionRight)
			m_InputData.m_Direction = 1;
		else if(m_InputDirectionLeft && m_InputDirectionRight)
			m_InputData.m_Direction = m_LastData.m_Direction ? -m_LastData.m_Direction : 1;

		// stress testing
		if(g_Config.m_DbgStress)
		{
			float t = Client()->LocalTime();
			mem_zero(&m_InputData, sizeof(m_InputData));

			m_InputData.m_Direction = ((int)t/2)&1;
			m_InputData.m_Jump = ((int)t);
			m_InputData.m_Fire = ((int)(t*10));
			m_InputData.m_Hook = ((int)(t*2))&1;
			m_InputData.m_WantedWeapon = ((int)t)%NUM_WEAPONS;
			m_InputData.m_TargetX = (int)(sinf(t*3)*100.0f);
			m_InputData.m_TargetY = (int)(cosf(t*3)*100.0f);
		}

		// send at at least 10hz
		if(time > LastSendTime + time_freq()/25)
			Send = true;
		
		if(!Send)
		{
			// check if we need to send input
			if(m_InputData.m_Direction != m_LastData.m_Direction) Send = true;
			else if(m_InputData.m_Jump != m_LastData.m_Jump) Send = true;
			else if(m_InputData.m_Fire != m_LastData.m_Fire) Send = true;
			else if(m_InputData.m_Hook != m_LastData.m_Hook) Send = true;
			else if(m_InputData.m_WantedWeapon != m_LastData.m_WantedWeapon) Send = true;
			else if(m_InputData.m_NextWeapon != m_LastData.m_NextWeapon) Send = true;
			else if(m_InputData.m_PrevWeapon != m_LastData.m_PrevWeapon) Send = true;
            else if(m_InputData.m_TargetX != m_LastData.m_TargetX) Send = true;
            else if(m_InputData.m_TargetY != m_LastData.m_TargetY) Send = true;
        }
	}

	// copy and return size
	m_LastData = m_InputData;

	if(!Send)
		return 0;

	LastSendTime = time;
	mem_copy(pData, &m_InputData, sizeof(m_InputData));
	return sizeof(m_InputData);
}

void CControls::OnRender()
{
	if(aimbot_smooth == 1)
		Aim();

	// update target pos
	if(m_pClient->m_Snap.m_pGameInfoObj && !m_pClient->m_Snap.m_SpecInfo.m_Active)
		m_TargetPos = m_pClient->m_LocalCharacterPos + m_MousePos;
	else if(m_pClient->m_Snap.m_SpecInfo.m_Active && m_pClient->m_Snap.m_SpecInfo.m_UsePosition)
		m_TargetPos = m_pClient->m_Snap.m_SpecInfo.m_Position + m_MousePos;
	else
		m_TargetPos = m_MousePos;
}

bool CControls::OnMouseMove(float x, float y)
{
	if((m_pClient->m_Snap.m_pGameInfoObj && m_pClient->m_Snap.m_pGameInfoObj->m_GameStateFlags&GAMESTATEFLAG_PAUSED) ||
		(m_pClient->m_Snap.m_SpecInfo.m_Active && m_pClient->m_pChat->IsActive()) || (aimbot != -1 && aimbot_smooth < 2))
		return false;

	m_MousePos += vec2(x, y); // TODO: ugly
	ClampMousePos();

	return true;
}

void CControls::ClampMousePos()
{
	if(m_pClient->m_Snap.m_SpecInfo.m_Active && !m_pClient->m_Snap.m_SpecInfo.m_UsePosition)
	{
		m_MousePos.x = clamp(m_MousePos.x, 0.0f, Collision()->GetWidth()*32.f);
		m_MousePos.y = clamp(m_MousePos.y, 0.0f, Collision()->GetHeight()*32.f);

	}
	else
	{
		const float CameraMaxDistance = 200.0f;
		const float FollowFactor = g_Config.m_ClMouseFollowfactor/100.0f;
		const float MouseMax = min(CameraMaxDistance/FollowFactor + g_Config.m_ClMouseDeadzone, (float)g_Config.m_ClMouseMaxDistance);
		const float MouseMax2 = MouseMax * MouseMax; // squared

		if((m_MousePos.x*m_MousePos.x + m_MousePos.y*m_MousePos.y) > MouseMax2) // lenght(m_MousePos) > sqrt(MouseMax)
			m_MousePos = normalize(m_MousePos)*MouseMax;
	}
}

void CControls::Aim()
{
	if(aimbot != -1 && m_pClient->m_Snap.m_aCharacters[aimbot].m_Active)
	{
		//const int localid = m_pClient->m_Snap.m_LocalClientID;
		
		vec2 pos_local = m_pClient->m_LocalCharacterPos;
		vec2 pos = m_pClient->m_aClients[aimbot].m_Predicted.m_Pos;
		
		if(m_pClient->m_Snap.m_SpecInfo.m_Active && m_pClient->m_Snap.m_SpecInfo.m_UsePosition)
		{
			//int specid = m_pClient->m_Snap.m_SpecInfo.m_SpectatorID;
			pos_local = m_pClient->m_Snap.m_SpecInfo.m_Position;
		}
		if(aimbot_predict != 0.f || aimbot_predict_dist != 0.f)
		{
			//vec2 vel_local = m_pClient->m_aClients[localid].m_Predicted.m_Vel;
			vec2 vel = m_pClient->m_aClients[aimbot].m_Predicted.m_Vel;
			
			pos += vel * aimbot_predict;
			//pos_local += vel_local * aimbot_predict;
            float dist = distance(pos, pos_local);
            
            pos += vel * (dist * aimbot_predict_dist);
            //pos_local += vel_local * (dist * aimbot_predict_dist);
		}
		
		if(m_pClient->m_Snap.m_SpecInfo.m_Active && !m_pClient->m_Snap.m_SpecInfo.m_UsePosition)
			m_MousePos = pos;
		else
			m_MousePos = pos - pos_local;
		m_TargetPos = pos;
		ClampMousePos();
	}
}

void CControls::AutoHook()
{
	// settings
	#define GETBIT(w,idx) (((w) >> (idx)) & 1)
	const bool hook_walls = GETBIT(auto_hook_type, 0),
		hook_players = GETBIT(auto_hook_type, 1),
		intellihook = GETBIT(auto_hook_type, 2),
		hook_once = GETBIT(auto_hook_type, 3); // only for intellihook
	#undef GETBIT
	
	const int LocalID = m_pClient->m_Snap.m_LocalClientID;
	
	if(!intellihook)
	{
		// dump autohook
		if(m_InputData.m_Hook)
		{
			const int hook_state = m_pClient->m_aClients[LocalID].m_Predicted.m_HookState;
			const int hooked_player = m_pClient->m_aClients[LocalID].m_Predicted.m_HookedPlayer;
			
			if(hook_state != HOOK_FLYING)
			{
				if(!(
					(hook_walls && hook_state == HOOK_GRABBED && hooked_player == -1) ||
					(hook_players && hook_state == HOOK_GRABBED && hooked_player != -1)
				))
				{
					m_InputData.m_Hook = 0;
				}
			}
		}
		else
		{
			// hook everything
			m_InputData.m_Hook = 1;
		}
	}
	else
	{
		// intelligent hook
		if(!m_InputData.m_Hook)
		{
			const vec2 Position = m_pClient->m_LocalCharacterPos;
			//const vec2 Direction = normalize(m_MousePos);
			const int Angle = round(atan2(m_MousePos.x, m_MousePos.y) * 256); // compress
			const vec2 Direction = vec2(sin(Angle/256.f), cos(Angle/256.f)); // decompress
			vec2 initPos = Position + Direction * 28.0f * 1.5f;
			vec2 finishPos = Position + Direction * (m_pClient->m_Tuning.m_HookLength - 18.0f);
			int Hit = Collision()->IntersectLine(initPos, finishPos, &finishPos, 0x0, true);
			if(hook_walls && Hit && !(Hit&CCollision::COLFLAG_NOHOOK))
			{
				// can hook
				m_InputData.m_Hook = 1;
			}
			else if(!Hit)
			{
				finishPos += Direction * 18.0f;
			}
			
			// hook characters
			if(!m_InputData.m_Hook && hook_players)
				if(m_pClient->IntersectCharacter(initPos, finishPos, finishPos, m_pClient->m_Tuning.m_HookFireSpeed, LocalID) != -1)
					m_InputData.m_Hook = 1;
		}
		else if(!hook_once)
		{
			const int hook_state = m_pClient->m_aClients[LocalID].m_Predicted.m_HookState;
			if(hook_state != HOOK_FLYING && hook_state != HOOK_GRABBED)
				m_InputData.m_Hook = 0;
		}
	}
}
