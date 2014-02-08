#include <game/server/score/logger.h>

#include <engine/shared/config.h>

#include <cstdio>
#include <ctime>

#ifdef _MSC_VER
#define PRId64 "lld"
#else
#include <cinttypes>
#endif

/*
 * Outputs a line to records.txt
 *
 *
 *  finish unixtime "map_name" id team start_tick current_tick "Name" "Clan"
 *
 *  checkpoint unixtime "map_name" id team checkpoint_id start_tick current_tick "Name" "Clan"
 *
 * 1 tick = 1 second / 50
 * finish time = ((current_tick - start_tick) / 50) seconds
 *
 */

//static LOCK gs_FileLock = 0;


static FILE * gs_File = 0;

/*
static struct LogArguments
{
    int id;
    char name[64];
    int team;
    char clan[64];
    int start_tick;
    int current_tick;

} gs_Args;
*/
void CScoreLogger::Init(IServer * pServer)
{
    m_pServer = pServer;
    gs_File = fopen("records.txt", "a");
    if(!gs_File)
        dbg_msg("scorelogger", "Unable to open records.txt");
}

/*
static void LogThread(void * ptype)
{
    int type = reinterpret_cast<int>(ptype);
    if(type == 1) // finish
    {
        // ....
        fprintf(gs_File, "finish %u %d %d %d %d \"%s\" \"%s\"\n"
                unixtime, gs_Args.id, gs_Args.team,
                gs_Args.start_tick, gs_Args.current_tick,
                gs_Args.name, gs_Args.clan);
    }
    else if(type == 2) // checkpoint
    {

    }
}


void CScoreLogger::LogFinish(int ClientID, int Team, int StartTick)
{
    void *pLogThread = thread_create(LogThread, (void*)1);
#if defined(CONF_FAMILY_UNIX)
    pthread_detach((pthread_t)pLogThread);
#endif
    (void)pLogThread;

}

void CScoreLogger::LogCheckpoint(int ClientID, int Team, int StartTick, int Checkpoint)
{
    void *pLogThread = thread_create(LogThread, (void*)2);
#if defined(CONF_FAMILY_UNIX)
    pthread_detach((pthread_t)pLogThread);
#endif
    (void)pLogThread;

}
*/

//template <typename InputInterator>
static void enquote(const char * in_first, char * out_first, char * out_end)
{
    out_end--; // \0
    while(out_first != out_end && *in_first)
    {
        if(*in_first == '\\' || *in_first == '"')
            *(out_first++) = '\\';
        if(out_first == out_end)
        {
            --out_first;
            break;
        }
        *(out_first++) = *(in_first++);
    }
    *out_first = '\0';
}


void CScoreLogger::LogFinish(int ClientID, int Team, int StartTick)
{
    int CurTick = Server()->Tick();
    time_t UnixTime = time(0);
    char Name[64], Clan[64];
    enquote(Server()->ClientName(ClientID), Name, Name + 64);
    enquote(Server()->ClientClan(ClientID), Clan, Clan + 64);
    fprintf(gs_File, "finish %" PRId64 " \"%s\" %d %d %d %d \"%s\" \"%s\"\n",
            (long long)UnixTime, g_Config.m_SvMap,
            ClientID, Team,
            StartTick, CurTick,
            Name, Clan);
    fflush(gs_File);
}
void CScoreLogger::LogCheckpoint(int ClientID, int Team, int StartTick, int Checkpoint)
{
    int CurTick = Server()->Tick();
    time_t UnixTime = time(0);
    char Name[64], Clan[64];
    enquote(Server()->ClientName(ClientID), Name, Name + 64);
    enquote(Server()->ClientClan(ClientID), Clan, Clan + 64);
    fprintf(gs_File, "checkpoint %" PRId64 " \"%s\" %d %d %d %d %d \"%s\" \"%s\"\n",
            (long long)UnixTime, g_Config.m_SvMap,
            ClientID, Team,
            Checkpoint,
            StartTick, CurTick,
            Name, Clan);
    fflush(gs_File);
}
