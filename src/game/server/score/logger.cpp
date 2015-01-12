#include <base/system.h>
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

static FILE * gs_File = 0;

void CScoreLogger::Init(IServer * pServer)
{
    m_pServer = pServer;
    if(!gs_File)
    {
        gs_File = fopen("records.txt", "a");
        if(!gs_File)
            dbg_msg("scorelogger", "Unable to open records.txt");
    }
}


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
            (int64)UnixTime, g_Config.m_SvMap,
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
            (int64)UnixTime, g_Config.m_SvMap,
            ClientID, Team,
            Checkpoint,
            StartTick, CurTick,
            Name, Clan);
    fflush(gs_File);
}
