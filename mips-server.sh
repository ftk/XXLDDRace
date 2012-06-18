#!/bin/sh -e
set -v
PATH=$PATH:/opt/toolchains/toolchain-mips_r2_gcc-4.7-linaro_uClibc-0.9.33.2/bin
export STAGING_DIR=.
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/demo.o src/engine/shared/demo.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/datafile.o src/engine/shared/datafile.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/network_client.o src/engine/shared/network_client.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/network_console_conn.o src/engine/shared/network_console_conn.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/packer.o src/engine/shared/packer.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/masterserver.o src/engine/shared/masterserver.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/filecollection.o src/engine/shared/filecollection.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/network_server.o src/engine/shared/network_server.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/linereader.o src/engine/shared/linereader.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/huffman.o src/engine/shared/huffman.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/console.o src/engine/shared/console.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/netban.o src/engine/shared/netban.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/econ.o src/engine/shared/econ.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/network_conn.o src/engine/shared/network_conn.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/network.o src/engine/shared/network.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/snapshot.o src/engine/shared/snapshot.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/config.o src/engine/shared/config.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/ringbuffer.o src/engine/shared/ringbuffer.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/network_console.o src/engine/shared/network_console.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/kernel.o src/engine/shared/kernel.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/memheap.o src/engine/shared/memheap.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/map.o src/engine/shared/map.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/jobs.o src/engine/shared/jobs.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/storage.o src/engine/shared/storage.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/mapchecker.o src/engine/shared/mapchecker.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/engine.o src/engine/shared/engine.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/shared/compression.o src/engine/shared/compression.cpp
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/base/system.o src/base/system.c
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/server/register.o src/engine/server/register.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/server/server.o src/engine/server/server.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/collision.o src/game/collision.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/localization.o src/game/localization.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/teamscore.o src/game/teamscore.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/layers.o src/game/layers.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/gamecore.o src/game/gamecore.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/score/sql_score.o src/game/server/score/sql_score.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/score/file_score.o src/game/server/score/file_score.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gameworld.o src/game/server/gameworld.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/memberlist.o src/game/server/memberlist.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/plasma.o src/game/server/entities/plasma.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/dragger.o src/game/server/entities/dragger.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/light.o src/game/server/entities/light.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/projectile.o src/game/server/entities/projectile.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/pickup.o src/game/server/entities/pickup.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/loltext.o src/game/server/entities/loltext.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/character.o src/game/server/entities/character.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/flag.o src/game/server/entities/flag.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/laser.o src/game/server/entities/laser.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/gun.o src/game/server/entities/gun.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entities/door.o src/game/server/entities/door.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/player.o src/game/server/player.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/eventhandler.o src/game/server/eventhandler.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gamecontroller.o src/game/server/gamecontroller.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gamemodes/tdm.o src/game/server/gamemodes/tdm.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gamemodes/dm.o src/game/server/gamemodes/dm.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gamemodes/ctf.o src/game/server/gamemodes/ctf.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gamemodes/mod.o src/game/server/gamemodes/mod.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gamemodes/DDRace.o src/game/server/gamemodes/DDRace.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/teams.o src/game/server/teams.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/entity.o src/game/server/entity.cpp
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/generated/server_data.o src/game/generated/server_data.cpp
#ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/gzclose.o src/engine/external/zlib/gzclose.c
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/generated/nethash.o src/game/generated/nethash.cpp
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/inffast.o src/engine/external/zlib/inffast.c
#ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/gzlib.o src/engine/external/zlib/gzlib.c
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/compress.o src/engine/external/zlib/compress.c
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/zutil.o src/engine/external/zlib/zutil.c
#ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/gzwrite.o src/engine/external/zlib/gzwrite.c
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/inflate.o src/engine/external/zlib/inflate.c
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/uncompr.o src/engine/external/zlib/uncompr.c
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/trees.o src/engine/external/zlib/trees.c
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/crc32.o src/engine/external/zlib/crc32.c
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/inftrees.o src/engine/external/zlib/inftrees.c
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/generated/protocol.o src/game/generated/protocol.cpp
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/deflate.o src/engine/external/zlib/deflate.c
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/ddracecommands.o src/game/server/ddracecommands.cpp
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/adler32.o src/engine/external/zlib/adler32.c
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/ddracechat.o src/game/server/ddracechat.cpp
#ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/gzread.o src/engine/external/zlib/gzread.c
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/game/server/gamecontext.o src/game/server/gamecontext.cpp
ccache mips-openwrt-linux-uclibc-gcc  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include"  -o objs/engine/external/zlib/infback.o src/engine/external/zlib/infback.c
ccache mips-openwrt-linux-uclibc-g++  -Wall -O3 -march=mips32r2 -c -DCONF_RELEASE -I "src" -I "other/mysql/include" -I "src/engine/external/zlib"  -o objs/engine/external/md5/md5.o src/engine/external/md5/md5.cpp
ccache mips-openwrt-linux-uclibc-g++ -o teeworlds_srv  objs/engine/shared/demo.o objs/engine/shared/datafile.o objs/engine/shared/network_client.o objs/engine/shared/network_console_conn.o objs/engine/shared/packer.o objs/engine/shared/masterserver.o objs/engine/shared/filecollection.o objs/engine/shared/network_server.o objs/engine/shared/linereader.o objs/engine/shared/huffman.o objs/engine/shared/console.o objs/engine/shared/netban.o objs/engine/shared/econ.o objs/engine/shared/network_conn.o objs/engine/shared/network.o objs/engine/shared/snapshot.o objs/engine/shared/config.o objs/engine/shared/ringbuffer.o objs/engine/shared/network_console.o objs/engine/shared/kernel.o objs/engine/shared/memheap.o objs/engine/shared/map.o objs/engine/shared/jobs.o objs/engine/shared/storage.o objs/engine/shared/mapchecker.o objs/engine/shared/engine.o objs/engine/shared/compression.o objs/base/system.o objs/engine/server/register.o objs/engine/server/server.o objs/game/collision.o objs/game/localization.o objs/game/gamecore.o objs/game/teamscore.o objs/game/layers.o objs/game/generated/nethash.o objs/game/generated/protocol.o objs/game/server/score/sql_score.o objs/game/server/score/file_score.o objs/game/server/ddracecommands.o objs/game/server/gameworld.o objs/game/server/memberlist.o objs/game/server/entities/plasma.o objs/game/server/entities/dragger.o objs/game/server/entities/light.o objs/game/server/entities/projectile.o objs/game/server/entities/pickup.o objs/game/server/entities/loltext.o objs/game/server/entities/character.o objs/game/server/entities/flag.o objs/game/server/entities/laser.o objs/game/server/entities/gun.o objs/game/server/entities/door.o objs/game/server/player.o objs/game/server/eventhandler.o objs/game/server/gamecontroller.o objs/game/server/gamemodes/tdm.o objs/game/server/gamemodes/dm.o objs/game/server/gamemodes/ctf.o objs/game/server/gamemodes/mod.o objs/game/server/gamemodes/DDRace.o objs/game/server/ddracechat.o objs/game/server/teams.o objs/game/server/entity.o objs/game/server/gamecontext.o objs/game/generated/server_data.o objs/engine/external/zlib/inffast.o objs/engine/external/zlib/compress.o objs/engine/external/zlib/zutil.o objs/engine/external/zlib/inflate.o objs/engine/external/zlib/uncompr.o objs/engine/external/zlib/trees.o objs/engine/external/zlib/crc32.o objs/engine/external/zlib/inftrees.o objs/engine/external/zlib/deflate.o objs/engine/external/zlib/adler32.o objs/engine/external/zlib/infback.o objs/engine/external/md5/md5.o -lpthread 
