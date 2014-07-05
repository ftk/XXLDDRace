/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_CLIENT_COMPONENTS_BINDS_H
#define GAME_CLIENT_COMPONENTS_BINDS_H
#include <game/client/component.h>
#include <engine/keys.h>
#include <engine/input.h>
#include <string>
#include <forward_list>
#include <utility>

class CBinds : public CComponent
{
	struct Bind
	{
		std::string line;
		std::forward_list<std::pair<unsigned, std::string> > modbinds;
		bool empty() const { return line.empty() && modbinds.empty(); }
		void clear() { line.clear(); modbinds.clear(); }
	};
	Bind m_aKeyBindings[KEY_LAST];

	int GetKeyID(const char *pKeyName);

	static void ConBind(IConsole::IResult *pResult, void *pUserData);
	static void ConUnbind(IConsole::IResult *pResult, void *pUserData);
	static void ConUnbindAll(IConsole::IResult *pResult, void *pUserData);
	static void ConDumpBinds(IConsole::IResult *pResult, void *pUserData);
	class IConsole *GetConsole() const { return Console(); }

	static void ConfigSaveCallback(class IConfig *pConfig, void *pUserData);

public:
	CBinds();

	class CBindsSpecial : public CComponent
	{
	public:
		CBinds *m_pBinds;
		virtual bool OnInput(IInput::CEvent Event);
	};

	CBindsSpecial m_SpecialBinds;

	void Bind(int KeyID, const char *pStr);
	void Bind(unsigned KeyID, unsigned KeyMods, const char *pStr);
	void SetDefaults();
	void UnbindAll();
	const char *Get(int KeyID);
	const char *GetKey(const char *pBindStr);

	virtual void OnConsoleInit();
	virtual bool OnInput(IInput::CEvent Event);

	// DDRace

	void SetDDRaceBinds(bool FreeOnly);

	static std::string KeyCombName(unsigned Key, unsigned Keymods);
	static std::pair<unsigned, unsigned> KeyCombByName(const std::string& KeyComb);

};
#endif
