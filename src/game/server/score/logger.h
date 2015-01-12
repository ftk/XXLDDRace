#ifndef GAME_SERVER_LOGGER_H
#define GAME_SERVER_LOGGER_H

#include <game/server/gamecontext.h>

#include <base/tl/threading.h>

class CScoreLogger
{

    class IServer * m_pServer;


    class IServer *Server()
    {
        return m_pServer;
    }
public:

    void Init(IServer * pServer);

    void LogFinish(int ClientID, int Team, int StartTick);
    void LogCheckpoint(int ClientID, int Team, int StartTick, int Checkpoint);
};




#endif

