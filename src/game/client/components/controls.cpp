/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <base/tl/sorted_array.h>

#include <base/math.h>

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
	auto_hook(false), hook_interval(0), aimbot(-1), aimbot_predict(0.f), aimbot_predict_dist(0.f)
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
	pSelf->hit_interval = (long long)(pResult->GetInteger(1)) * time_freq() / 1000LL;
}

static void ConAutoHook(IConsole::IResult *pResult, void *pUserData)
{
	CControls *pSelf = (CControls *)pUserData;
	pSelf->auto_hook = !!pResult->GetInteger(0);
	if(!pSelf->auto_hook)
		pSelf->m_InputData.m_Hook = 0;
	pSelf->hook_interval = (long long)(pResult->GetInteger(1)) * time_freq() / 1000LL;
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
	
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(!pSelf->pClient->m_Snap.m_aCharacters[i].m_Active || i == pSelf->pClient->m_Snap.m_LocalClientID)
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
void CControls::OnConsoleInit()
{
	// game commands
	Console()->Register("+left", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputDirectionLeft, "Move left");
	Console()->Register("+right", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputDirectionRight, "Move right");
	Console()->Register("+jump", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputData.m_Jump, "Jump");
	Console()->Register("+hook", "", CFGFLAG_CLIENT, ConKeyInputState, &m_InputData.m_Hook, "Hook");
	Console()->Register("+fire", "", CFGFLAG_CLIENT, ConKeyInputCounter, &m_InputData.m_Fire, "Fire");

	Console()->Register("mouse", "ff", CFGFLAG_CLIENT, ConMousePos, this, "Set mouse position");
	Console()->Register("mouse_angle", "f", CFGFLAG_CLIENT, ConMouseAngle, this, "Set mouse angle in degree");
	{ static CMouseGet s_Set = {&m_MousePos, &m_TargetPos, Console()}; Console()->Register("mouse_get", "", CFGFLAG_CLIENT, ConMouseGet, (void *)&s_Set, "Get mouse position and angle"); }
	
	Console()->Register("autohit", "ii", CFGFLAG_CLIENT, ConAutoHit, this, "Spam-click fire");
	Console()->Register("+autohit", "i", CFGFLAG_CLIENT, ConAutoHit, this, "Spam-click fire");
	Console()->Register("autohook", "ii", CFGFLAG_CLIENT, ConAutoHook, this, "Spam-click hook");
	Console()->Register("+autohook", "i", CFGFLAG_CLIENT, ConAutoHook, this, "Spam-click hook");
	Console()->Register("+aimbot", "i", CFGFLAG_CLIENT, ConAimbotLock, this, "Aimbot lock to player");
	{ static CAimbot s_Set = {m_pClient, this}; Console()->Register("+aimbotnear", "", CFGFLAG_CLIENT, ConAimbot, (void *)&s_Set, "Aimbot lock to the nearest player"); }
    Console()->Register("aimbot_predict", "f", CFGFLAG_CLIENT, ConAimbotPredict, this, "Set aimbot prediction");
    Console()->Register("aimbot_dist", "f", CFGFLAG_CLIENT, ConAimbotPredictDistance, this, "Set aimbot prediction distance multiplier");

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
	static int64 last_hook_time = 0;

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

	if(m_LastData.m_PlayerFlags != m_InputData.m_PlayerFlags)
		Send = true;

	m_LastData.m_PlayerFlags = m_InputData.m_PlayerFlags;

	if(auto_hit && last_hit_time + hit_interval < time)
	{
		m_InputData.m_Fire = (m_InputData.m_Fire + 31) & INPUT_STATE_MASK;
		last_hit_time = time;
		Send = true;
	}
	if(auto_hook) // rehook
	{
		if(m_InputData.m_Hook)
		{
			if(last_hook_time + hook_interval < time)
			{
				m_InputData.m_Hook = 0;
				Send = true;
			}
		}
		else
		{
			m_InputData.m_Hook = 1;
			last_hook_time = time;
			Send = true;
		}
	}
	if(aimbot != -1 && m_pClient->m_Snap.m_aCharacters[aimbot].m_Active)
	{
		int localid = m_pClient->m_Snap.m_LocalClientID;
		const CNetObj_Character& Prev = m_pClient->m_Snap.m_aCharacters[aimbot].m_Prev;
		const CNetObj_Character& Cur = m_pClient->m_Snap.m_aCharacters[aimbot].m_Cur;
		const CNetObj_Character& PrevLocal = m_pClient->m_Snap.m_aCharacters[localid].m_Prev;
		const CNetObj_Character& CurLocal = m_pClient->m_Snap.m_aCharacters[localid].m_Cur;
		
		//float IntraTick = Client()->IntraGameTick();
		
		//vec2 pos = mix(vec2(Prev.m_X, Prev.m_Y), vec2(Cur.m_X, Cur.m_Y), IntraTick);
		vec2 pos = vec2(Cur.m_X, Cur.m_Y);
		vec2 pos_local = m_pClient->m_LocalCharacterPos;
		
		if(aimbot_predict != 0.f || aimbot_predict_dist != 0.f)
		{
			//vec2 vel = mix(vec2(Prev.m_VelX/256.f, Prev.m_VelY/256.f), vec2(Cur.m_VelX/256.f, Cur.m_VelY/256.f), IntraTick);
			//vec2 vel_local = mix(vec2(PrevLocal.m_VelX/256.f, PrevLocal.m_VelY/256.f), vec2(CurLocal.m_VelX/256.f, CurLocal.m_VelY/256.f), IntraTick);
			vec2 vel = vec2(Cur.m_VelX/256.f, Cur.m_VelY/256.f);
			vec2 vel_local = vec2(CurLocal.m_VelX/256.f, CurLocal.m_VelY/256.f);
								
			pos += vel * aimbot_predict;
			pos_local += vel_local * aimbot_predict;
            float dist = distance(pos, pos_local);
            
            pos += vel * (dist * aimbot_predict_dist);
            pos_local += vel_local * (dist * aimbot_predict_dist);
		}
		
		if(m_pClient->m_Snap.m_SpecInfo.m_Active && !m_pClient->m_Snap.m_SpecInfo.m_UsePosition)
			m_MousePos = pos;
		else
			m_MousePos = pos - pos_local;
		m_TargetPos = pos;
		ClampMousePos();
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
		float c = 1.f;
		if(!m_pClient->m_Snap.m_SpecInfo.m_Active)
			c = 256.f;
		m_InputData.m_TargetX = round(m_MousePos.x * c);
		m_InputData.m_TargetY = round(m_MousePos.y * c);

		if(!m_InputData.m_TargetX && !m_InputData.m_TargetY)
		{
			m_InputData.m_TargetX = 1;
		}

		// set direction
		m_InputData.m_Direction = 0;
		if(m_InputDirectionLeft && !m_InputDirectionRight)
			m_InputData.m_Direction = -1;
		if(!m_InputDirectionLeft && m_InputDirectionRight)
			m_InputData.m_Direction = 1;

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
		(m_pClient->m_Snap.m_SpecInfo.m_Active && m_pClient->m_pChat->IsActive()))
		return false;

	m_MousePos += vec2(x, y); // TODO: ugly
	ClampMousePos();

	return true;
}

void CControls::ClampMousePos()
{
	if(m_pClient->m_Snap.m_SpecInfo.m_Active && !m_pClient->m_Snap.m_SpecInfo.m_UsePosition)
	{
		m_MousePos.x = clamp(m_MousePos.x, 200.0f, Collision()->GetWidth()*32-200.0f);
		m_MousePos.y = clamp(m_MousePos.y, 200.0f, Collision()->GetHeight()*32-200.0f);

	}
	else
	{
		float CameraMaxDistance = 200.0f;
		float FollowFactor = g_Config.m_ClMouseFollowfactor/100.0f;
		float MouseMax = min(CameraMaxDistance/FollowFactor + g_Config.m_ClMouseDeadzone, (float)g_Config.m_ClMouseMaxDistance);

		if(length(m_MousePos) > MouseMax)
			m_MousePos = normalize(m_MousePos)*MouseMax;
	}
}
