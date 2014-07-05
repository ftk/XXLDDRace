/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/config.h>
#include <engine/shared/config.h>
#include "binds.h"

bool CBinds::CBindsSpecial::OnInput(IInput::CEvent Event)
{
	// don't handle invalid events and keys that arn't set to anything
	if(Event.m_Key >= KEY_F1 && Event.m_Key <= KEY_F15 && !m_pBinds->m_aKeyBindings[Event.m_Key].empty())
	{
		int Stroke = 0;
		if(Event.m_Flags&IInput::FLAG_PRESS)
			Stroke = 1;

		if(!m_pBinds->m_aKeyBindings[Event.m_Key].line.empty())
			m_pBinds->GetConsole()->ExecuteLineStroked(Stroke, m_pBinds->m_aKeyBindings[Event.m_Key].line.c_str());
		
		if(!m_pBinds->m_aKeyBindings[Event.m_Key].modbinds.empty())
		{
			unsigned Mods = Event.GetKeyMods(); 
			for(const auto& pair : m_pBinds->m_aKeyBindings[Event.m_Key].modbinds)
			{
				bool exec = (Mods & pair.first) == pair.first;
				if(!pair.first) // binds "+key" can only execute when no keymods applied
					exec = Mods == 0;
				if(exec)
					m_pBinds->GetConsole()->ExecuteLineStroked(Stroke, pair.second.c_str());
			}
		}
		return true;
	}

	return false;
}

CBinds::CBinds()
{
	m_SpecialBinds.m_pBinds = this;
}

void CBinds::Bind(int KeyID, const char *pStr)
{
	if(KeyID < 0 || KeyID >= KEY_LAST)
		return;

	m_aKeyBindings[KeyID].line = pStr;
	char aBuf[1024];
	if(m_aKeyBindings[KeyID].line.empty())
		str_format(aBuf, sizeof(aBuf), "unbound %s (%d)", IInput::KeyName(KeyID), KeyID);
	else
		str_format(aBuf, sizeof(aBuf), "bound %s (%d) = %s", IInput::KeyName(KeyID), KeyID, m_aKeyBindings[KeyID].line.c_str());
	Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "binds", aBuf);
}

void CBinds::Bind(unsigned KeyID, unsigned KeyMods, const char *pStr)
{
	if(KeyID >= KEY_LAST)
		return;

	std::string * line = NULL;
	for(auto it = m_aKeyBindings[KeyID].modbinds.begin(), before = m_aKeyBindings[KeyID].modbinds.before_begin();
	    it != m_aKeyBindings[KeyID].modbinds.end(); before = it, ++it)
	{
		if(it->first == KeyMods)
		{
			if(pStr[0])
			{
				line = &(it->second);
				*line = pStr;
			}
			else // unbind
				m_aKeyBindings[KeyID].modbinds.erase_after(before);
			break;
		}
	}
	if(!line && pStr[0])
	{
	        m_aKeyBindings[KeyID].modbinds.push_front(std::make_pair(KeyMods, std::string(pStr)));
		line = &(m_aKeyBindings[KeyID].modbinds.front().second);
	}
		

	const std::string KeyName = KeyCombName(KeyID, KeyMods);
	char aBuf[1024];
	if(!line)
		str_format(aBuf, sizeof(aBuf), "unbound %s (%d:%u)", KeyName.c_str(), KeyID, KeyMods);
	else
		str_format(aBuf, sizeof(aBuf), "bound %s (%d:%u) = %s", KeyName.c_str(), KeyID, KeyMods, line->c_str());
	Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "binds", aBuf);
}


bool CBinds::OnInput(IInput::CEvent e)
{
	// don't handle invalid events and keys that arn't set to anything
	if(e.m_Key <= 0 || e.m_Key >= KEY_LAST || m_aKeyBindings[e.m_Key].empty())
		return false;

	int Stroke = 0;
	if(e.m_Flags&IInput::FLAG_PRESS)
		Stroke = 1;
	if(!m_aKeyBindings[e.m_Key].line.empty())
		Console()->ExecuteLineStroked(Stroke, m_aKeyBindings[e.m_Key].line.c_str());

	if(!m_aKeyBindings[e.m_Key].modbinds.empty())
	{
		unsigned Mods = e.GetKeyMods(); 
		for(const auto& pair : m_aKeyBindings[e.m_Key].modbinds)
		{
			bool exec = (Mods & pair.first) == pair.first;
			if(!pair.first) // binds "+key" can only execute when no keymods applied
				exec = Mods == 0;
			if(exec)
			        Console()->ExecuteLineStroked(Stroke, pair.second.c_str());
		}
	}
	return true;
}

void CBinds::UnbindAll()
{
	for(int i = 0; i < KEY_LAST; i++)
		m_aKeyBindings[i].clear();
}

const char *CBinds::Get(int KeyID)
{
	if(KeyID > 0 && KeyID < KEY_LAST)
		return m_aKeyBindings[KeyID].line.c_str();
	return "";
}

const char *CBinds::GetKey(const char *pBindStr)
{
	for(int KeyId = 0; KeyId < KEY_LAST; KeyId++)
	{
		const char *pBind = Get(KeyId);
		if(!pBind[0])
			continue;

		if(str_comp(pBind, pBindStr) == 0)
			return IInput::KeyName(KeyId);
	}

	return "";
}

void CBinds::SetDefaults()
{
	// set default key bindings
	UnbindAll();
	Bind(KEY_F1, "toggle_local_console");
	Bind(KEY_F2, "toggle_remote_console");
	Bind(KEY_TAB, "+scoreboard");
	Bind('u', "+show_chat");
	Bind(KEY_F10, "screenshot");

	Bind('a', "+left");
	Bind('d', "+right");

	Bind(KEY_SPACE, "+jump");
	Bind(KEY_MOUSE_1, "+fire");
	Bind(KEY_MOUSE_2, "+hook");
	Bind(KEY_LSHIFT, "+emote");
	Bind(KEY_RSHIFT, "+spectate");
	Bind(KEY_RIGHT, "spectate_next");
	Bind(KEY_LEFT, "spectate_previous");

	Bind('1', "+weapon1");
	Bind('2', "+weapon2");
	Bind('3', "+weapon3");
	Bind('4', "+weapon4");
	Bind('5', "+weapon5");

	Bind(KEY_MOUSE_WHEEL_UP, "+prevweapon");
	Bind(KEY_MOUSE_WHEEL_DOWN, "+nextweapon");

	Bind('t', "chat all");
	Bind('y', "chat team");

	Bind(KEY_F3, "vote yes");
	Bind(KEY_F4, "vote no");

	// DDRace

	if(g_Config.m_ClDDRaceBinds)
		SetDDRaceBinds(false);
}

void CBinds::OnConsoleInit()
{
	// bindings
	IConfig *pConfig = Kernel()->RequestInterface<IConfig>();
	if(pConfig)
		pConfig->RegisterCallback(ConfigSaveCallback, this);

	Console()->Register("bind", "sr", CFGFLAG_CLIENT, ConBind, this, "Bind key to execute the command");
	Console()->Register("unbind", "s", CFGFLAG_CLIENT, ConUnbind, this, "Unbind key");
	Console()->Register("unbindall", "", CFGFLAG_CLIENT, ConUnbindAll, this, "Unbind all keys");
	Console()->Register("dump_binds", "", CFGFLAG_CLIENT, ConDumpBinds, this, "Dump binds");

	// default bindings
	SetDefaults();
}

void CBinds::ConBind(IConsole::IResult *pResult, void *pUserData)
{
	CBinds *pBinds = (CBinds *)pUserData;
	const char *pKeyName = pResult->GetString(0);
	std::pair<unsigned, unsigned> KeyComb = KeyCombByName(pKeyName);
	unsigned id = KeyComb.first, keymods = KeyComb.second;

	if(!id)
	{
		char aBuf[256];
		str_format(aBuf, sizeof(aBuf), "key %s not found", pKeyName);
		pBinds->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "binds", aBuf);
		return;
	}

	if(!keymods && pKeyName[0] != '+')
		pBinds->Bind(id, pResult->GetString(1));
	else
		pBinds->Bind(id, keymods, pResult->GetString(1));
}


void CBinds::ConUnbind(IConsole::IResult *pResult, void *pUserData)
{
	CBinds *pBinds = (CBinds *)pUserData;
	const char *pKeyName = pResult->GetString(0);
	std::pair<unsigned, unsigned> KeyComb = KeyCombByName(pKeyName);
	unsigned id = KeyComb.first, keymods = KeyComb.second;

	if(!id)
	{
		char aBuf[256];
		str_format(aBuf, sizeof(aBuf), "key %s not found", pKeyName);
		pBinds->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "binds", aBuf);
		return;
	}
	
	if(!keymods && pKeyName[0] != '+')
		pBinds->Bind(id, "");
	else
		pBinds->Bind(id, keymods, "");
}


void CBinds::ConUnbindAll(IConsole::IResult *pResult, void *pUserData)
{
	CBinds *pBinds = (CBinds *)pUserData;
	pBinds->UnbindAll();
}


void CBinds::ConDumpBinds(IConsole::IResult *pResult, void *pUserData)
{
	CBinds *pBinds = (CBinds *)pUserData;
	char aBuf[1024];
	for(int i = 0; i < KEY_LAST; i++)
	{
		if(pBinds->m_aKeyBindings[i].empty())
			continue;
		str_format(aBuf, sizeof(aBuf), "%s (%d) = %s", IInput::KeyName(i), i, pBinds->m_aKeyBindings[i].line.c_str());
		pBinds->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "binds", aBuf);
	}
}

int CBinds::GetKeyID(const char *pKeyName)
{
	// check for numeric
	if(pKeyName[0] == '&')
	{
		int i = str_toint(pKeyName+1);
		if(i > 0 && i < KEY_LAST)
			return i; // numeric
	}

	// search for key
	for(int i = 0; i < KEY_LAST; i++)
	{
		if(str_comp(pKeyName, IInput::KeyName(i)) == 0)
			return i;
	}

	return 0;
}

void CBinds::ConfigSaveCallback(IConfig *pConfig, void *pUserData)
{
	CBinds *pSelf = (CBinds *)pUserData;

	pConfig->WriteLine("unbindall");

	auto write_bind = [] (IConfig *pConfig, const char * key, const char * line) {
		char aBuffer[1024];
		char *pEnd = aBuffer+sizeof(aBuffer)-8;
		
		str_format(aBuffer, sizeof(aBuffer), "bind %s ", key);
		const char *pSrc = line;

		// process the string. we need to escape some characters
		char *pDst = aBuffer + str_length(aBuffer);
		*pDst++ = '"';
		while(*pSrc && pDst < pEnd)
		{
			if(*pSrc == '"' || *pSrc == '\\') // escape \ and "
				*pDst++ = '\\';
			*pDst++ = *pSrc++;
		}
		*pDst++ = '"';
		*pDst++ = 0;

		pConfig->WriteLine(aBuffer);		
	};
	
	for(int i = 0; i < KEY_LAST; i++)
	{
		if(pSelf->m_aKeyBindings[i].empty())
			continue;

		if(!pSelf->m_aKeyBindings[i].line.empty())
			write_bind(pConfig, IInput::KeyName(i), pSelf->m_aKeyBindings[i].line.c_str());
		
		for(const auto& pair : pSelf->m_aKeyBindings[i].modbinds)
		{
			const std::string key = KeyCombName(i, pair.first);
			write_bind(pConfig, key.c_str(), pair.second.c_str());
		}
	}
}

// DDRace

void CBinds::SetDDRaceBinds(bool FreeOnly)
{
	#if 0
	if(!FreeOnly)
	{
		Bind(KEY_KP_PLUS, "zoom+");
		Bind(KEY_KP_MINUS, "zoom-");
		Bind(KEY_KP_MULTIPLY, "zoom");
		Bind(KEY_HOME, "kill");
		Bind(KEY_PAUSE, "say /pause");
		Bind(KEY_UP, "+jump");
		Bind(KEY_LEFT, "+left");
		Bind(KEY_RIGHT, "+right");
		Bind('[', "+prevweapon");
		Bind(']', "+nextweapon");
		Bind('c', "say /rank");
		Bind('v', "say /info");
		Bind('b', "say /top5");
		Bind('z', "emote 12");
		Bind('x', "emote 14");
		Bind('h', "emote 2");
		Bind('m', "emote 5");
		Bind(KEY_PAGEDOWN, "cl_show_entities 0");
		Bind(KEY_PAGEUP, "cl_show_entities 1");
		Bind(KEY_KP0, "say /emote normal 999999");
		Bind(KEY_KP1, "say /emote happy 999999");
		Bind(KEY_KP2, "say /emote angry 999999");
		Bind(KEY_KP3, "say /emote pain 999999");
		Bind(KEY_KP4, "say /emote surprise 999999");
		Bind(KEY_KP5, "say /emote blink 999999");
		Bind(KEY_MOUSE_3, "+spectate");
	}
	else
	{
		if(!Get(KEY_KP_PLUS)[0])
			Bind(KEY_KP_PLUS, "zoom+");
		if(!Get(KEY_KP_MINUS)[0])
			Bind(KEY_KP_MINUS, "zoom-");
		if(!Get(KEY_KP_MULTIPLY)[0])
			Bind(KEY_KP_MULTIPLY, "zoom");
		if(!Get(KEY_HOME)[0])
			Bind(KEY_HOME, "kill");
		if(!Get(KEY_PAUSE)[0])
			Bind(KEY_PAUSE, "say /pause");
		if(!Get(KEY_UP)[0])
			Bind(KEY_UP, "+jump");
		if(!Get(KEY_LEFT)[0])
			Bind(KEY_LEFT, "+left");
		if(!Get(KEY_RIGHT)[0])
			Bind(KEY_RIGHT, "+right");
		if(!Get('[')[0])
			Bind('[', "+prevweapon");
		if(!Get(']')[0])
			Bind(']', "+nextweapon");
		if(!Get('c')[0])
			Bind('c', "say /rank");
		if(!Get('v')[0])
			Bind('v', "say /info");
		if(!Get('b')[0])
			Bind('b', "say /top5");
		if(!Get('z')[0])
			Bind('z', "emote 12");
		if(!Get('x')[0])
			Bind('x', "emote 14");
		if(!Get(KEY_KP_PLUS)[0])
			Bind('h', "emote 2");
		if(!Get('m')[0])
			Bind('m', "emote 5");
		if(!Get(KEY_PAGEDOWN)[0])
			Bind(KEY_PAGEDOWN, "cl_show_entities 0");
		if(!Get(KEY_PAGEUP)[0])
			Bind(KEY_PAGEUP, "cl_show_entities 1");
		if(!Get(KEY_KP0)[0])
			Bind(KEY_KP0, "say /emote normal 999999");
		if(!Get(KEY_KP1)[0])
			Bind(KEY_KP1, "say /emote happy 999999");
		if(!Get(KEY_KP2)[0])
			Bind(KEY_KP2, "say /emote angry 999999");
		if(!Get(KEY_KP3)[0])
			Bind(KEY_KP3, "say /emote pain 999999");
		if(!Get(KEY_KP4)[0])
			Bind(KEY_KP4, "say /emote surprise 999999");
		if(!Get(KEY_KP5)[0])
			Bind(KEY_KP5, "say /emote blink 999999");
		if(!Get(KEY_MOUSE_3)[0])
			Bind(KEY_MOUSE_3, "+spectate");
		if(!Get(KEY_MINUS)[0])
			Bind(KEY_MINUS, "spectate_previous");
		if(!Get(KEY_EQUALS)[0])
			Bind(KEY_EQUALS, "spectate_next");
	}
		g_Config.m_ClDDRaceBindsSet = 1;
		#endif
}

std::pair<unsigned, unsigned> CBinds::KeyCombByName(const std::string& KeyComb) 
{
	// parse key combination, e.g. lshift+k; lctrl+lshift+space; +space
	unsigned Key = 0, Keymods = 0;
	std::size_t lastidx = 0;
	std::size_t idx = KeyComb.find_first_of('+', 0);
	while(idx != std::string::npos)
	{
		if(idx == 0) // +key
		{
			lastidx = 1;
			break;
		}
		const std::string KeymodName = KeyComb.substr(lastidx, idx - lastidx);
		for(int i = 1; i < KEYMOD_TOTAL; i++)
		{
			if(IInput::KeyName(g_aaKeymods[i][1]) == KeymodName)
				Keymods |= g_aaKeymods[i][0];
		}
		lastidx = idx + 1;
		idx = KeyComb.find_first_of('+', lastidx);
	}
	// guess key name
	const std::string Name = KeyComb.substr(lastidx);
	for(int i = 0; i < KEY_LAST; i++)
	{
		if(IInput::KeyName(i) == Name)
		{
			Key = i;
			break;
		}
	}
	return std::make_pair(Key, Keymods);
}

std::string CBinds::KeyCombName(unsigned Key, unsigned Keymods)
{
	// generate key combination
	std::string result;
	for(int i = 1; i < KEYMOD_TOTAL; i++)
	{
		if((Keymods & g_aaKeymods[i][0]) == g_aaKeymods[i][0])
		{
			result += IInput::KeyName(g_aaKeymods[i][1]);
			result += '+';
		}
	}
	if(result.empty())
		result += '+';
	result += IInput::KeyName(Key);
	return result;
}
