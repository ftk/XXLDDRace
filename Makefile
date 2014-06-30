CPPFLAGS := -flto -O3 -march=native -msse2 -msse3 -msse4.2 -mfpmath=both -mavx -pipe -fno-exceptions -fvisibility=internal \
-Wall -DCONF_RELEASE -DNO_VIZ -I "src" -I "other/mysql/include" -I "src/engine/external/zlib" -I "other/sdl/include" -I "other/freetype/include"
CXXFLAGS := -std=c++11 -fno-rtti
CFLAGS :=
LDFLAGS := -flto -O3 -march=native -s -static-libgcc -static-libstdc++

CC := gcc
CXX := g++
LD := g++
PYTHON := python
WINDRES := windres

srcs_to_objs = $(patsubst src/%.c,objs/%.o,$(patsubst src/%.cpp,objs/%.o,$(1)))

all: XXLDDRace.exe XXLDDRace-Server_32.exe

headers := $(wildcard src/engine/external/wavpack/*.h src/engine/external/zlib/*.h src/engine/external/pnglite/*.h src/engine/external/md5/*.h src/engine/shared/*.h src/base/*.h src/base/threading/*.h src/game/*.h)

wavpack := $(wildcard src/engine/external/wavpack/*.c)
zlib := $(wildcard src/engine/external/zlib/*.c)
pnglite := $(wildcard src/engine/external/pnglite/*.c)
md5 := src/engine/external/md5/md5.cpp

engine := $(wildcard src/engine/shared/*.cpp src/base/*.c)
client := $(wildcard src/engine/client/*.cpp)
server := $(wildcard src/engine/server/*.cpp)

game_shared := $(wildcard src/game/*.cpp) src/game/generated/protocol.cpp
game_client := $(wildcard src/game/client/*.cpp src/game/client/components/*.cpp) src/game/generated/client_data.cpp
game_server := $(wildcard src/game/server/*.cpp src/game/server/entities/*.cpp src/game/server/gamemodes/*.cpp  \
	src/game/server/score/*.cpp)  src/game/generated/server_data.cpp
game_editor := $(wildcard src/game/editor/*.cpp)

versionsrv := $(wildcard src/versionsrv/*.cpp)
mastersrv := $(wildcard src/mastersrv/*.cpp)
banmaster := $(wildcard src/banmaster/*.cpp)

generated_h := src/game/generated/protocol.h src/game/generated/server_data.h src/game/generated/client_data.h src/game/generated/nethash.cpp
generated_cpp := src/game/generated/protocol.cpp src/game/generated/server_data.cpp src/game/generated/client_data.cpp 
generated := $(generated_h) $(generated_cpp) other/icons/teeworlds_srv_gcc.coff other/icons/teeworlds_gcc.coff


objs/%.o: src/%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o '$@' '$<'
objs/%.o: src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o '$@' '$<'


client_srcs := $(engine) $(client) $(game_shared) $(game_client) $(game_editor) $(zlib) $(wavpack) $(pnglite)
client_objs := $(call srcs_to_objs,$(client_srcs))



XXLDDRace.exe: $(client_objs) other/icons/teeworlds_gcc.coff
	$(LD) $(LDFLAGS) -o '$@' $^ -Lother/sdl/lib64 -Lother/freetype/lib64 -lws2_32 -lgdi32 -lopengl32 -lglu32 -lfreetype -lSDL -lSDLmain


server_srcs := $(engine) $(server) $(game_shared) $(game_server)  $(zlib) $(md5)
server_objs := $(call srcs_to_objs,$(server_srcs))


XXLDDRace-Server_32.exe: $(server_objs) other/icons/teeworlds_srv_gcc.coff
	$(LD) $(LDFLAGS) -o '$@' $^ -lws2_32

$(client_objs) $(server_objs): $(generated_h) $(headers)

clean:
	-rm $(sort $(client_objs) $(server_objs) XXLDDRace.exe XXLDDRace-Server_32.exe $(generated) )

src/game/generated/protocol.h:
	$(PYTHON) datasrc/compile.py network_header > $@
src/game/generated/protocol.cpp:
	$(PYTHON) datasrc/compile.py network_source > $@
src/game/generated/nethash.cpp: src/engine/shared/protocol.h src/game/generated/protocol.h src/game/tuning.h src/game/gamecore.cpp
	-$(PYTHON) scripts/cmd5.py $^ > $@
src/game/generated/server_data.h:
	$(PYTHON) datasrc/compile.py server_content_header > $@
src/game/generated/server_data.cpp:
	$(PYTHON) datasrc/compile.py server_content_source > $@
src/game/generated/client_data.h:
	$(PYTHON) datasrc/compile.py client_content_header > $@
src/game/generated/client_data.cpp:
	$(PYTHON) datasrc/compile.py client_content_source > $@

%.coff: %.rc
	$(WINDRES) -i $< -o $@



