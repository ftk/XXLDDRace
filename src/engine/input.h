/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "kernel.h"
#include "keys.h"

extern const char * g_aaKeyStrings[KEY_LAST];
extern const unsigned g_aaKeymods[KEYMOD_TOTAL][2];

class IInput : public IInterface
{
	MACRO_INTERFACE("input", 0)
public:
	class CEvent
	{
	public:
		unsigned m_Flags; // first 2 bits : FLAG_PRESS, FLAG_RELEASE, other: KEYMOD_ modifilers
		int m_Unicode;
		int m_Key;

		unsigned GetKeyMods() const { return m_Flags >> 2; }
	};

protected:
	enum
	{
		INPUT_BUFFER_SIZE=32
	};

	// quick access to events
	int m_NumEvents;
	IInput::CEvent m_aInputEvents[INPUT_BUFFER_SIZE];

	//quick access to input
	struct
	{
		unsigned char m_Presses;
		unsigned char m_Releases;
	} m_aInputCount[2][KEY_LAST];

	unsigned char m_aInputState[2][KEY_LAST];
	int m_InputCurrent;
	bool m_InputDispatched;

	int KeyWasPressed(int Key) { return m_aInputState[m_InputCurrent^1][Key]; }

public:
	enum
	{
		FLAG_PRESS=1,
		FLAG_RELEASE=2
	};

	static unsigned SetKeyMods(unsigned Flags, unsigned KeyMod)
	{
		Flags &= 3u; // clear everything except first 2 bits
		Flags |= KeyMod << 2;
		return Flags;
	}

	// events
	int NumEvents() const { return m_NumEvents; }
	void ClearEvents() 
	{ 
		m_NumEvents = 0;
		m_InputDispatched = true;
	}
	CEvent GetEvent(int Index) const
	{
		if(Index < 0 || Index >= m_NumEvents)
		{
			IInput::CEvent e = {0,0};
			return e;
		}
		return m_aInputEvents[Index];
	}

	// keys
	int KeyPressed(unsigned Key) { return (Key < KEY_LAST) ? m_aInputState[m_InputCurrent][Key] : 0; }
	int KeyReleases(unsigned Key) { return (Key < KEY_LAST) ? m_aInputCount[m_InputCurrent][Key].m_Releases : 0; }
	int KeyPresses(unsigned Key) { return (Key < KEY_LAST) ? m_aInputCount[m_InputCurrent][Key].m_Presses : 0; }
	int KeyDown(unsigned Key) { return (Key < KEY_LAST) ? (KeyPressed(Key)&&!KeyWasPressed(Key)) : 0; }
	static const char *KeyName(unsigned Key) { return (Key < KEY_LAST) ? g_aaKeyStrings[Key] : g_aaKeyStrings[0]; }

	//
	virtual void MouseModeRelative() = 0;
	virtual void MouseModeAbsolute() = 0;
	virtual int MouseDoubleClick() = 0;

	virtual void MouseRelative(float *x, float *y) = 0;
	
};


class IEngineInput : public IInput
{
	MACRO_INTERFACE("engineinput", 0)
public:
	virtual void Init() = 0;
	virtual int Update() = 0;
};

extern IEngineInput *CreateEngineInput();

#endif
