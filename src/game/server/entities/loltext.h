#ifndef GAME_SERVER_ENTITIES_LOLTEXT_H
#define GAME_SERVER_ENTITIES_LOLTEXT_H

#include <game/server/entity.h>

//usage: GameServer()->CreateLoltext(...)
//it will dispose itself after lifespan ended

class CLolPlasma : public CEntity
{
public:
	//position relative to pParent->m_Pos. if pParent is NULL, Pos is absolute. lifespan in ticks
	CLolPlasma(CGameWorld *pGameWorld, CEntity *pParent, vec2 Pos, vec2 Vel, int Lifespan);

	virtual void Reset();
	virtual void Tick();
	virtual void Snap(int SnappingClient);


private:
	vec2 m_LocalPos; // local coordinate system is origin'd wherever we actually start (i.e. this is (0,0) after creation)
	vec2 m_Vel;
	int m_Life; // remaining ticks
	int m_StartTick; // tick created
	vec2 m_StartOff; // initial offset from parent, for proper following
	CEntity *m_pParent;
};

class CLoltext
{
private:
	static unsigned long long s_aChars[128];
        static unsigned long long GetRepr(int c);
public:
	static vec2 TextSize(const char *pText);
	static void Create(CGameWorld *pGameWorld, CEntity *pParent, vec2 Pos, vec2 Vel, int Lifespan, const char *pText, bool Center, bool Follow);
};

#endif

