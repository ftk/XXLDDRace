/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef ENGINE_SHARED_CONFIG_VARIABLES_H
#define ENGINE_SHARED_CONFIG_VARIABLES_H
#undef ENGINE_SHARED_CONFIG_VARIABLES_H // this file will be included several times

// TODO: remove this
#include "././game/variables.h"


MACRO_CONFIG_STR(PlayerName, player_name, 16, "nameless tee", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Name of the player")
MACRO_CONFIG_STR(PlayerClan, player_clan, 12, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Clan of the player")
MACRO_CONFIG_INT(PlayerCountry, player_country, -1, -1, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Country of the player")
MACRO_CONFIG_STR(Password, password, 32, "", CFGFLAG_CLIENT|CFGFLAG_SERVER, "Password to the server")
MACRO_CONFIG_STR(Logfile, logfile, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER, "Filename to log all output to")
MACRO_CONFIG_INT(ConsoleOutputLevel, console_output_level, 0, 0, 2, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Adjusts the amount of information in the console")

MACRO_CONFIG_INT(ClCpuThrottle, cl_cpu_throttle, 0, 0, 100, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(ClEditor, cl_editor, 0, 0, 1, CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(ClLoadCountryFlags, cl_load_country_flags, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Load and show country flags")

MACRO_CONFIG_INT(ClAutoDemoRecord, cl_auto_demo_record, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Automatically record demos")
MACRO_CONFIG_INT(ClAutoDemoMax, cl_auto_demo_max, 10, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Maximum number of automatically recorded demos (0 = no limit)")
MACRO_CONFIG_INT(ClAutoScreenshot, cl_auto_screenshot, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Automatically take game over screenshot")
MACRO_CONFIG_INT(ClAutoScreenshotMax, cl_auto_screenshot_max, 10, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Maximum number of automatically created screenshots (0 = no limit)")

MACRO_CONFIG_INT(ClEventthread, cl_eventthread, 0, 0, 1, CFGFLAG_CLIENT, "Enables the usage of a thread to pump the events")

MACRO_CONFIG_INT(InpGrab, inp_grab, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use forceful input grabbing method")

MACRO_CONFIG_STR(BrFilterString, br_filter_string, 25, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Server browser filtering string")
MACRO_CONFIG_INT(BrFilterFull, br_filter_full, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out full server in browser")
MACRO_CONFIG_INT(BrFilterEmpty, br_filter_empty, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out empty server in browser")
MACRO_CONFIG_INT(BrFilterSpectators, br_filter_spectators, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out spectators from player numbers")
MACRO_CONFIG_INT(BrFilterFriends, br_filter_friends, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out servers with no friends")
MACRO_CONFIG_INT(BrFilterCountry, br_filter_country, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out servers with non-matching player country")
MACRO_CONFIG_INT(BrFilterCountryIndex, br_filter_country_index, -1, -1, 999, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Player country to filter by in the server browser")
MACRO_CONFIG_INT(BrFilterPw, br_filter_pw, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out password protected servers in browser")
MACRO_CONFIG_INT(BrFilterPing, br_filter_ping, 999, 0, 999, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Ping to filter by in the server browser")
MACRO_CONFIG_STR(BrFilterGametype, br_filter_gametype, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Game types to filter")
MACRO_CONFIG_INT(BrFilterGametypeStrict, br_filter_gametype_strict, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Strict gametype filter")
MACRO_CONFIG_STR(BrFilterServerAddress, br_filter_serveraddress, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Server address to filter")
MACRO_CONFIG_INT(BrFilterPure, br_filter_pure, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out non-standard servers in browser")
MACRO_CONFIG_INT(BrFilterPureMap, br_filter_pure_map, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out non-standard maps in browser")
MACRO_CONFIG_INT(BrFilterCompatversion, br_filter_compatversion, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Filter out non-compatible servers in browser")

MACRO_CONFIG_INT(BrSort, br_sort, 0, 0, 256, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(BrSortOrder, br_sort_order, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(BrMaxRequests, br_max_requests, 25, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Number of requests to use when refreshing server browser")

MACRO_CONFIG_INT(SndBufferSize, snd_buffer_size, 512, 128, 32768, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound buffer size")
MACRO_CONFIG_INT(SndRate, snd_rate, 48000, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound mixing rate")
MACRO_CONFIG_INT(SndEnable, snd_enable, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound enable")
MACRO_CONFIG_INT(SndMusic, snd_enable_music, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Play background music")
MACRO_CONFIG_INT(SndVolume, snd_volume, 100, 0, 100, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound volume")
MACRO_CONFIG_INT(SndDevice, snd_device, -1, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "(deprecated) Sound device to use")

MACRO_CONFIG_INT(SndNonactiveMute, snd_nonactive_mute, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(SndChat, snd_chat, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")

MACRO_CONFIG_INT(GfxScreenWidth, gfx_screen_width, 800, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen resolution width")
MACRO_CONFIG_INT(GfxScreenHeight, gfx_screen_height, 600, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen resolution height")
MACRO_CONFIG_INT(GfxBorderless, gfx_borderless, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Borderless window (not to be used with fullscreen)")
MACRO_CONFIG_INT(GfxFullscreen, gfx_fullscreen, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Fullscreen")
MACRO_CONFIG_INT(GfxAlphabits, gfx_alphabits, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Alpha bits for framebuffer (fullscreen only)")
MACRO_CONFIG_INT(GfxColorDepth, gfx_color_depth, 24, 16, 24, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Colors bits for framebuffer (fullscreen only)")
MACRO_CONFIG_INT(GfxClear, gfx_clear, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Clear screen before rendering")
MACRO_CONFIG_INT(GfxVsync, gfx_vsync, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Vertical sync")
MACRO_CONFIG_INT(GfxDisplayAllModes, gfx_display_all_modes, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(GfxTextureCompression, gfx_texture_compression, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use texture compression")
MACRO_CONFIG_INT(GfxHighDetail, gfx_high_detail, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "High detail")
MACRO_CONFIG_INT(GfxTextureQuality, gfx_texture_quality, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(GfxFsaaSamples, gfx_fsaa_samples, 0, 0, 16, CFGFLAG_SAVE|CFGFLAG_CLIENT, "FSAA Samples")
MACRO_CONFIG_INT(GfxRefreshRate, gfx_refresh_rate, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen refresh rate")
MACRO_CONFIG_INT(GfxFinish, gfx_finish, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(GfxAsyncRender, gfx_asyncrender, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Do rendering async from the the update")

MACRO_CONFIG_INT(GfxThreaded, gfx_threaded, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use the threaded graphics backend")

MACRO_CONFIG_INT(InpMousesens, inp_mousesens, 100, -5000, 100000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Mouse sensitivity")

MACRO_CONFIG_STR(SvName, sv_name, 128, "unnamed server", CFGFLAG_SERVER, "XXLDDRace Default")
MACRO_CONFIG_STR(Bindaddr, bindaddr, 128, "", CFGFLAG_CLIENT|CFGFLAG_SERVER|CFGFLAG_MASTER, "Address to bind the client/server to")
MACRO_CONFIG_INT(SvPort, sv_port, 8303, 0, 0, CFGFLAG_SERVER, "Port to use for the server")
MACRO_CONFIG_INT(SvExternalPort, sv_external_port, 0, 0, 0, CFGFLAG_SERVER, "External port to report to the master servers")
MACRO_CONFIG_STR(SvMap, sv_map, 128, "dm1", CFGFLAG_SERVER, "Map to use on the server")
MACRO_CONFIG_INT(SvMaxClients, sv_max_clients, 16, 1, MAX_CLIENTS, CFGFLAG_SERVER, "Maximum number of clients that are allowed on a server")
MACRO_CONFIG_INT(SvMaxClientsPerIP, sv_max_clients_per_ip, 2, 1, MAX_CLIENTS, CFGFLAG_SERVER, "Maximum number of clients with the same IP that can connect to the server")
MACRO_CONFIG_INT(SvHighBandwidth, sv_high_bandwidth, 0, 0, 1, CFGFLAG_SERVER, "Use high bandwidth mode. Doubles the bandwidth required for the server. LAN use only")
MACRO_CONFIG_INT(SvRegister, sv_register, 1, 0, 1, CFGFLAG_SERVER, "Register server with master server for public listing")
MACRO_CONFIG_STR(SvRconPassword, sv_rcon_password, 32, "", CFGFLAG_SERVER, "Remote console password (full access)")
MACRO_CONFIG_STR(SvRconModPassword, sv_rcon_mod_password, 32, "", CFGFLAG_SERVER, "Remote console password for moderators (limited access)")
MACRO_CONFIG_INT(SvRconMaxTries, sv_rcon_max_tries, 30, 0, 100, CFGFLAG_SERVER, "Maximum number of tries for remote console authentication")
MACRO_CONFIG_INT(SvRconBantime, sv_rcon_bantime, 5, 0, 1440, CFGFLAG_SERVER, "The time a client gets banned if remote console authentication fails. 0 makes it just use kick")
MACRO_CONFIG_INT(SvAutoDemoRecord, sv_auto_demo_record, 0, 0, 1, CFGFLAG_SERVER, "Automatically record demos")
MACRO_CONFIG_INT(SvAutoDemoMax, sv_auto_demo_max, 10, 0, 1000, CFGFLAG_SERVER, "Maximum number of automatically recorded demos (0 = no limit)")

MACRO_CONFIG_STR(EcBindaddr, ec_bindaddr, 128, "localhost", CFGFLAG_ECON, "Address to bind the external console to. Anything but 'localhost' is dangerous")
MACRO_CONFIG_INT(EcPort, ec_port, 0, 0, 0, CFGFLAG_ECON, "Port to use for the external console")
MACRO_CONFIG_STR(EcPassword, ec_password, 32, "", CFGFLAG_ECON, "External console password")
MACRO_CONFIG_INT(EcBantime, ec_bantime, 0, 0, 1440, CFGFLAG_ECON, "The time a client gets banned if econ authentication fails. 0 just closes the connection")
MACRO_CONFIG_INT(EcAuthTimeout, ec_auth_timeout, 30, 1, 120, CFGFLAG_ECON, "Time in seconds before the the econ authentification times out")
MACRO_CONFIG_INT(EcOutputLevel, ec_output_level, 1, 0, 2, CFGFLAG_ECON, "Adjusts the amount of information in the external console")

MACRO_CONFIG_INT(Debug, debug, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Debug mode")
MACRO_CONFIG_INT(DbgStress, dbg_stress, 0, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Stress systems")
MACRO_CONFIG_INT(DbgStressNetwork, dbg_stress_network, 0, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Stress network")
MACRO_CONFIG_INT(DbgPref, dbg_pref, 0, 0, 1, CFGFLAG_SERVER, "Performance outputs")
MACRO_CONFIG_INT(DbgGraphs, dbg_graphs, 0, 0, 1, CFGFLAG_CLIENT, "Performance graphs")
MACRO_CONFIG_INT(DbgHitch, dbg_hitch, 0, 0, 0, CFGFLAG_SERVER, "Hitch warnings")
MACRO_CONFIG_STR(DbgStressServer, dbg_stress_server, 32, "localhost", CFGFLAG_CLIENT, "Server to stress")
MACRO_CONFIG_INT(DbgResizable, dbg_resizable, 0, 0, 0, CFGFLAG_CLIENT, "Enables window resizing")

MACRO_CONFIG_INT(ClWalkSpeed, cl_walk_speed, 100, 1, 100000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Walk animation speed(inv)")
MACRO_CONFIG_STR(LicenseKey, license, 16, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "License key")

// DDRace

MACRO_CONFIG_STR(SvWelcome, sv_welcome, 64, "", CFGFLAG_SERVER, "Message that will be displayed to players who join the server")
MACRO_CONFIG_INT(SvReservedSlots, sv_reserved_slots, 0, 0, 16, CFGFLAG_SERVER, "The number of slots that are reserved for special players")
MACRO_CONFIG_STR(SvReservedSlotsPass, sv_reserved_slots_pass, 32, "", CFGFLAG_SERVER, "The password that is required to use a reserved slot")
MACRO_CONFIG_INT(SvHit, sv_hit, 1, 0, 1, CFGFLAG_SERVER, "Whether players can hammer/grenade/laser eachother or not")
MACRO_CONFIG_INT(SvEndlessDrag, sv_endless_drag, 0, 0, 1, CFGFLAG_SERVER, "Turns endless hooking on/off")
MACRO_CONFIG_INT(SvTestingCommands, sv_test_cmds, 0, 0, 1, CFGFLAG_SERVER, "Turns testing commands aka cheats on/off")
MACRO_CONFIG_INT(SvFreezeDelay, sv_freeze_delay, 3, 1, 30, CFGFLAG_SERVER, "How many seconds the players will remain frozen (applies to all except delayed freeze in switch layer & deepfreeze)")
MACRO_CONFIG_INT(ClDDRaceBinds, cl_race_binds, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Enable Default DDRace builds when pressing the reset binds button")
MACRO_CONFIG_INT(ClDDRaceBindsSet, cl_race_binds_set, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Whether the DDRace binds set or not (this is automated you don't need to use this)")
MACRO_CONFIG_INT(SvEndlessSuperHook, sv_endless_super_hook, 0, 0, 1, CFGFLAG_SERVER, "Endless hook for super players on/off")
MACRO_CONFIG_INT(SvHideScore, sv_hide_score, 0, 0, 1, CFGFLAG_SERVER, "Whether players scores will be announced or not")
MACRO_CONFIG_INT(SvPauseable, sv_pauseable, 1, 0, 1, CFGFLAG_SERVER, "Whether players can pause their char or not")
MACRO_CONFIG_INT(SvPauseTime, sv_pause_time, 0, 0, 1, CFGFLAG_SERVER, "Whether '/pause' and 'sv_max_dc_restore' pauses the time of player or not")
MACRO_CONFIG_INT(SvPauseFrequency, sv_pause_frequency, 1, 0, 9999, CFGFLAG_SERVER, "The minimum allowed delay between pauses")

MACRO_CONFIG_INT(SvEmotionalTees, sv_emotional_tees, 1, -1, 1, CFGFLAG_SERVER, "Whether eye change of tees is enabled with emoticons = 1, not = 0, -1 not at all")
MACRO_CONFIG_INT(SvEmoticonDelay, sv_emoticon_delay, 500, 0, 99999, CFGFLAG_SERVER, "The time in milliseconds between over-head emoticons")
MACRO_CONFIG_INT(SvEyeEmoteChangeDelay, sv_eye_emote_change_delay, 1, 0, 9999, CFGFLAG_SERVER, "The time in seconds between eye emoticons change")


MACRO_CONFIG_INT(SvChatDelay, sv_chat_delay, 1, 0, 9999, CFGFLAG_SERVER, "The time in seconds between chat messages")
MACRO_CONFIG_INT(SvTeamChangeDelay, sv_team_change_delay, 3, 0, 9999, CFGFLAG_SERVER, "The time in seconds between team changes (spectator/in game)")
MACRO_CONFIG_INT(SvInfoChangeDelay, sv_info_change_delay, 5, 0, 9999, CFGFLAG_SERVER, "The time in seconds between info changes (name/skin/color), to avoid ranbow mod set this to a very high time")
MACRO_CONFIG_INT(SvVoteMapTimeDelay, sv_vote_map_delay,0,0,9999,CFGFLAG_SERVER, "The minimum time in seconds between map votes")
MACRO_CONFIG_INT(SvVoteDelay, sv_vote_delay, 3, 0, 9999, CFGFLAG_SERVER, "The time in seconds between any vote")
MACRO_CONFIG_INT(SvVoteKickTimeDelay, sv_vote_kick_delay, 0, 0, 9999, CFGFLAG_SERVER, "The minimum time in seconds between kick votes")
MACRO_CONFIG_INT(SvVoteYesPercentage, sv_vote_yes_percentage, 50, 1, 100, CFGFLAG_SERVER, "The percent of people that need to agree or deny for the vote to succeed/fail")
MACRO_CONFIG_INT(SvVoteMajority, sv_vote_majority, 0, 0, 1, CFGFLAG_SERVER, "Whether No. of Yes is compared to No. of No votes or to number of total Players ( Default is 0 Y compare N)")
MACRO_CONFIG_INT(SvSpectatorVotes, sv_spectator_votes, 1, 0, 1, CFGFLAG_SERVER, "Choose if spectators are allowed to start votes")
MACRO_CONFIG_INT(SvKillDelay, sv_kill_delay,1,0,9999,CFGFLAG_SERVER, "The minimum time in seconds between kills")
MACRO_CONFIG_INT(SvSuicidePenalty, sv_suicide_penalty,0,0,9999,CFGFLAG_SERVER, "The minimum time in seconds between kill or /kills and respawn")

MACRO_CONFIG_INT(SvMapWindow, sv_map_window, 30, 0, 100, CFGFLAG_SERVER, "Map downloading send-ahead window")
MACRO_CONFIG_INT(SvFastDownload, sv_fast_download, 1, 0, 1, CFGFLAG_SERVER, "Enables fast download of maps")

MACRO_CONFIG_INT(SvShotgunBulletSound, sv_shotgun_bullet_sound, 0, 0, 1, CFGFLAG_SERVER, "Crazy shotgun bullet sound on/off")

MACRO_CONFIG_INT(SvCheckpointSave, sv_checkpoint_save, 1, 0, 1, CFGFLAG_SERVER, "Whether to save checkpoint times to the score file")
MACRO_CONFIG_STR(SvScoreFolder, sv_score_folder, 32, "records", CFGFLAG_SERVER, "Folder to save score files to")

#if defined(CONF_SQL)
MACRO_CONFIG_INT(SvUseSQL, sv_use_sql, 0, 0, 1, CFGFLAG_SERVER, "Enables SQL DB instead of record file")
MACRO_CONFIG_STR(SvSqlUser, sv_sql_user, 32, "nameless", CFGFLAG_SERVER, "SQL User")
MACRO_CONFIG_STR(SvSqlPw, sv_sql_pw, 32, "tee", CFGFLAG_SERVER, "SQL Password")
MACRO_CONFIG_STR(SvSqlIp, sv_sql_ip, 32, "127.0.0.1", CFGFLAG_SERVER, "SQL Database IP")
MACRO_CONFIG_INT(SvSqlPort, sv_sql_port, 3306, 0, 65535, CFGFLAG_SERVER, "SQL Database port")
MACRO_CONFIG_STR(SvSqlDatabase, sv_sql_database, 16, "teeworlds", CFGFLAG_SERVER, "SQL Database name")
MACRO_CONFIG_STR(SvSqlPrefix, sv_sql_prefix, 16, "record", CFGFLAG_SERVER, "SQL Database table prefix")
#endif

MACRO_CONFIG_INT(SvDDRaceRules, sv_ddrace_rules, 1, 0, 1, CFGFLAG_SERVER, "Whether the default mod rules are displayed or not")
MACRO_CONFIG_STR(SvRulesLine1, sv_rules_line1, 40, "", CFGFLAG_SERVER, "Rules line 1")
MACRO_CONFIG_STR(SvRulesLine2, sv_rules_line2, 40, "", CFGFLAG_SERVER, "Rules line 2")
MACRO_CONFIG_STR(SvRulesLine3, sv_rules_line3, 40, "", CFGFLAG_SERVER, "Rules line 3")
MACRO_CONFIG_STR(SvRulesLine4, sv_rules_line4, 40, "", CFGFLAG_SERVER, "Rules line 4")
MACRO_CONFIG_STR(SvRulesLine5, sv_rules_line5, 40, "", CFGFLAG_SERVER, "Rules line 5")
MACRO_CONFIG_STR(SvRulesLine6, sv_rules_line6, 40, "", CFGFLAG_SERVER, "Rules line 6")
MACRO_CONFIG_STR(SvRulesLine7, sv_rules_line7, 40, "", CFGFLAG_SERVER, "Rules line 7")
MACRO_CONFIG_STR(SvRulesLine8, sv_rules_line8, 40, "", CFGFLAG_SERVER, "Rules line 8")
MACRO_CONFIG_STR(SvRulesLine9, sv_rules_line9, 40, "", CFGFLAG_SERVER, "Rules line 9")
MACRO_CONFIG_STR(SvRulesLine10, sv_rules_line10, 40, "", CFGFLAG_SERVER, "Rules line 10")

MACRO_CONFIG_INT(SvTeam, sv_team, 1, 0, 2, CFGFLAG_SERVER, "Teams configuration (0 = off, 1 = on but optional, 2 = must play only with teams)")

MACRO_CONFIG_STR(SvAnnouncementFileName, sv_announcement_filename, 24, "announcement.txt", CFGFLAG_SERVER, "file which will have the announcement, each one at a line")
MACRO_CONFIG_INT(SvAnnouncementInterval, sv_announcement_interval, 30, 15, 9999, CFGFLAG_SERVER, "time(minutes) in which the announcement will be displayed from the announcement file")
MACRO_CONFIG_INT(SvAnnouncementRandom, sv_announcement_random, 1, 0, 1, CFGFLAG_SERVER, "Whether announcements are sequential or random")

MACRO_CONFIG_INT(SvOldLaser, sv_old_laser, 0, 0, 1, CFGFLAG_SERVER, "Whether lasers can hit you if you shot them and that they pull you towards the bounce origin (0 for DDRace Beta) or lasers can't hit you if you shot them, and they pull others towards the shooter")
MACRO_CONFIG_INT(SvSlashMe, sv_slash_me, 0, 0, 1, CFGFLAG_SERVER, "Whether /me is active on the server or not")

MACRO_CONFIG_INT(ConnTimeout, conn_timeout, 15, 5, 100, CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER, "Network timeout")
MACRO_CONFIG_INT(ClShowIDs, cl_show_ids, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Whether to show client ids in scoreboard")
MACRO_CONFIG_INT(ClAutoRaceRecord, cl_auto_race_record, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Save the best demo of each race")
MACRO_CONFIG_INT(ClDemoName, cl_demo_name, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Save the player name within the demo")
MACRO_CONFIG_INT(ClRaceGhost, cl_race_ghost, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Enable ghost")
MACRO_CONFIG_INT(ClRaceShowGhost, cl_race_show_ghost, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show ghost")
MACRO_CONFIG_INT(ClRaceSaveGhost, cl_race_save_ghost, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Save ghost")
MACRO_CONFIG_INT(ClDDRaceScoreBoard, cl_ddrace_scoreboard, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Enable DDRace Scoreboard ")
MACRO_CONFIG_INT(SvResetPickus, sv_reset_pickups, 0, 0, 1, CFGFLAG_SERVER, "Whether the weapons are reset on passing the start tile or not")
MACRO_CONFIG_INT(ClShowOthers, cl_show_others, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show players in other teams")
MACRO_CONFIG_INT(ClShowEntities, cl_show_entities, 0, 0, 1, CFGFLAG_CLIENT, "Cheat to show game tiles, background: 1 = blue, 2 = black")
MACRO_CONFIG_INT(ClShowQuads, cl_show_quads, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show quads")
MACRO_CONFIG_INT(ClMapBackground, cl_map_background, 7777777, 0, 0xFFFFFF, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Background color for maphack")
MACRO_CONFIG_INT(ClLocalPredict, cl_local_predict, 1, 0, 1, CFGFLAG_CLIENT, "Use client data for local client")
MACRO_CONFIG_INT(SvShowOthers, sv_show_others, 1, 0, 1, CFGFLAG_SERVER, "Whether players can user the command showothers or not")
MACRO_CONFIG_INT(SvMaxAfkTime, sv_max_afk_time, 0, 0, 9999, CFGFLAG_SERVER, "The time in seconds a player is allowed to be afk (0 = disabled)")
MACRO_CONFIG_INT(SvPlasmaRange, sv_plasma_range, 700, 1, 99999, CFGFLAG_SERVER, "How far will the plasma gun track tees")
MACRO_CONFIG_INT(SvPlasmaPerSec, sv_plasma_per_sec, 3, 0, 50, CFGFLAG_SERVER, "How many shots does the plasma gun fire per seconds")
MACRO_CONFIG_INT(SvVotePause, sv_vote_pause, 1, 0, 1, CFGFLAG_SERVER, "Allow voting to pause players (instead of moving to spectators)")
MACRO_CONFIG_INT(SvVotePauseTime, sv_vote_pause_time, 10, 0, 360, CFGFLAG_SERVER, "The time (in seconds) players have to wait in pause when paused by vote")
MACRO_CONFIG_INT(SvTuneReset, sv_tune_reset, 0, 0, 1, CFGFLAG_SERVER, "Whether tuning is reset after each map change or not")
MACRO_CONFIG_INT(SvDDRaceTuneReset, sv_ddrace_tune_reset, 1, 0, 1, CFGFLAG_SERVER, "Whether DDRace tuning(sv_hit, Sv_Endless_Drag & Sv_Old_Laser) is reset after each map change or not")
MACRO_CONFIG_INT(SvNamelessScore, sv_nameless_score, 0, 0, 1, CFGFLAG_SERVER, "Whether nameless tee has a score or not")
MACRO_CONFIG_INT(SvTimeInBroadcastInterval, sv_time_in_broadcast_interval, 1, 0, 60, CFGFLAG_SERVER, "How often to update the broadcast time")
MACRO_CONFIG_INT(SvDefaultTimerType, sv_default_timer_type, 0, 0, 1, CFGFLAG_SERVER, "Default way of displaying time either game/round timer or broadcast. 0 = game/round timer, 1 = broadcast")

MACRO_CONFIG_INT(ClRideThreshold1, cl_ride_threshold1, 75, 1, 500000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "RIDEBOT> Slowing down distance")
MACRO_CONFIG_INT(ClRideThreshold2, cl_ride_threshold2, 5, 0, 5000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "RIDEBOT> Dead zone")
MACRO_CONFIG_INT(ClRideSet, cl_ride_set, 2, 0, 2, CFGFLAG_SAVE|CFGFLAG_CLIENT, "RIDEBOT> Self coordinates 0:Local | 1:Server | 2:Predicted")

MACRO_CONFIG_INT(ClAimline, cl_aimline, 0, 0, 250, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Aim line point frequency")
MACRO_CONFIG_INT(ClHUDSolo, cl_hud_solo, 0, 0, 2, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Solo indicator> 0:Chat 1:Icon+Chat 2:Icon")

MACRO_CONFIG_STR(ClQuitMessageText, cl_quit_message, 256, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Set custom disconnecting reason")
MACRO_CONFIG_INT(ClNoRenderTime, cl_norender_time, 0, 0, 999, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Don't render for x ms after swapping buffers")
MACRO_CONFIG_INT(ClDamageIndTime, cl_damageind_time, 500, 0, 99999, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Damage indicator time in ms")
MACRO_CONFIG_INT(ClDamageIndSpeed, cl_damageind_speed, 500, 0, 99999, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Damage indicator speed")

// these might need some fine tuning
MACRO_CONFIG_INT(SvChatPenalty, sv_chat_penalty, 250, 50, 1000, CFGFLAG_SERVER, "chat score will be increased by this on every message, and decremented by 1 on every tick.")
MACRO_CONFIG_INT(SvChatThreshold, sv_chat_threshold, 1000, 50, 10000 , CFGFLAG_SERVER, "if chats core exceeds this, the player will be muted for sv_spam_mute_duration seconds")
MACRO_CONFIG_INT(SvSpamMuteDuration, sv_spam_mute_duration, 60, 0, 3600 , CFGFLAG_SERVER, "how many seconds to mute, if player triggers mute on spam. 0 = off")

// banmaster
MACRO_CONFIG_INT(SvGlobalBantime, sv_global_ban_time, 60, 0, 1440, CFGFLAG_SERVER, "The time a client gets banned if the ban server reports it. 0 to disable")


//XXLmod client:
MACRO_CONFIG_INT(GfxFullClear, gfx_full_clear, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Show gamelayer")
MACRO_CONFIG_INT(GfxMiniTees, gfx_mini_tees, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Cute!!!! Minitees")

//XXLmod server:
MACRO_CONFIG_STR(SvRconSubAdminPassword, sv_rcon_subadmin_pass, 32, "", CFGFLAG_SERVER, "Remote console subadministrator password")
MACRO_CONFIG_STR(SvRconHelperPassword, sv_rcon_helper_password, 32, "", CFGFLAG_SERVER, "Remote console password for helpers (limited access)")
MACRO_CONFIG_INT(SvDmgBlood, sv_dmg_blood, 0, 0, 1, CFGFLAG_SERVER, "Turns blood on damage on/off")
MACRO_CONFIG_INT(SvRescue, sv_rescue, 0, 0, 1, CFGFLAG_SERVER, "Turns rescue /r on/off")
MACRO_CONFIG_INT(SvRescueDelay, sv_rescue_delay, 100, 0, 600000, CFGFLAG_SERVER, "Set the delay between rescue in milliseconds")
MACRO_CONFIG_INT(SvRescueEffects, sv_rescue_effect, 0, 0, 1, CFGFLAG_SERVER, "Turns rescue effects on/off")
MACRO_CONFIG_INT(SvLolFilter, sv_lol_filter, 0, 0, 1, CFGFLAG_SERVER, "Turns 'lol' filter on/off")
MACRO_CONFIG_INT(SvHelper, sv_helper, 1, 0, 1, CFGFLAG_SERVER, "Turns /helper on/off")
MACRO_CONFIG_INT(SvSilentXXL, sv_silent_xxl, 0, 0, 1, CFGFLAG_SERVER, "Makes XXL silent.")
MACRO_CONFIG_INT(SvRconScore, sv_rcon_score, 0, 0, 1, CFGFLAG_SERVER, "Shows the rcon lvl in scoreboard.")
MACRO_CONFIG_INT(SvWhisperLevel, sv_whisper_lvl, 1, -1, 4, CFGFLAG_SERVER, "Sets the rcon lvl to whisper")
MACRO_CONFIG_INT(SvWhisperAdmin, sv_whisper_allow_to_admin, 0, 0, 1, CFGFLAG_SERVER, "Allows to whisper to admins")
MACRO_CONFIG_INT(SvLaserScore, sv_laser_score, 0, 0, 1, CFGFLAG_SERVER, "Shows new score and checkpoints in laserfont above the player")
MACRO_CONFIG_INT(SvRMNinjaResetVel, sv_rmninja_reset_vel, 0, 0, 1, CFGFLAG_SERVER, "Shows new score and checkpoints in laserfont above the player")
MACRO_CONFIG_INT(SvFainbowFeet, sv_rainbow_feet, 0, 0, 1, CFGFLAG_SERVER, "The feets of the tees are rainbow")

MACRO_CONFIG_INT(SvSwap, sv_swap, 0, 0, 1, CFGFLAG_SERVER, "Turns /swap on/off")

#endif
