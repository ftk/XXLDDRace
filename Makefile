CPPFLAGS := -flto -O3 -march=native -msse2 -msse3 -msse4.2 -mfpmath=both -mavx -pipe -fno-exceptions \
-Wall -DCONF_RELEASE -DNO_VIZ -I "src" -I "other/mysql/include" -I "src/engine/external/zlib" -I "other/sdl/include" -I "other/freetype/include"
CXXFLAGS := -std=gnu++0x -fno-rtti
CFLAGS :=
LDFLAGS := -flto -O3 -march=native -msse2 -msse3 -msse4.2 -mfpmath=both -mavx -fno-exceptions -fno-rtti  -static-libgcc -static-libstdc++

CC = gcc
CXX = g++

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

generated_h := src/game/generated/protocol.h src/game/generated/server_data.h src/game/generated/client_data.h src/game/generated/nethash.cpp
generated_cpp := src/game/generated/protocol.cpp src/game/generated/server_data.cpp src/game/generated/client_data.cpp 
generated := $(generated_h) $(generated_cpp) other/icons/teeworlds_srv_gcc.coff other/icons/teeworlds_gcc.coff


objs/%.o: src/%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o '$@' '$<'
objs/%.o: src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o '$@' '$<'


client_srcs := $(engine) $(client) $(game_shared) $(game_client) $(game_editor) $(zlib) $(wavpack) $(pnglite)
client_objs0 := $(client_srcs:src/%.cpp=objs/%.o)
client_objs := $(client_objs0:src/%.c=objs/%.o)


$(client_objs): $(generated_h) $(headers)

XXLDDRace.exe: $(client_objs) other/icons/teeworlds_gcc.coff
	$(CXX) $(LDFLAGS) -o '$@' $^ -Lother/sdl/lib64 -Lother/freetype/lib64 -lgdi32 -luser32 -lws2_32 -lole32 -lshell32 -lopengl32 -lglu32 -lwinmm -lfreetype -lSDL -lSDLmain


server_srcs := $(engine) $(server) $(game_shared) $(game_server)  $(zlib) $(md5)
server_objs0 := $(server_srcs:src/%.cpp=objs/%.o)
server_objs := $(server_objs0:src/%.c=objs/%.o)


XXLDDRace-Server_32.exe: $(server_objs) other/icons/teeworlds_srv_gcc.coff
	$(CXX) $(LDFLAGS) -o '$@' $(server_objs) other/icons/teeworlds_srv_gcc.coff -lgdi32 -luser32 -lws2_32 -lole32 -lshell32


clean:
	-rm $(client_objs) XXLDDRace.exe XXLDDRace-Server_32.exe $(generated)

src/game/generated/protocol.h:
	python datasrc/compile.py network_header > $@
src/game/generated/protocol.cpp:
	python datasrc/compile.py network_source > $@
src/game/generated/nethash.cpp: src/engine/shared/protocol.h src/game/generated/protocol.h src/game/tuning.h src/game/gamecore.cpp
	-python scripts/cmd5.py $^ > $@
src/game/generated/server_data.h:
	python datasrc/compile.py server_content_header > $@
src/game/generated/server_data.cpp:
	python datasrc/compile.py server_content_source > $@
src/game/generated/client_data.h:
	python datasrc/compile.py client_content_header > $@
src/game/generated/client_data.cpp:
	python datasrc/compile.py client_content_source > $@

#$(generated_cpp:src/%.cpp=objs/%.o): $(generated_cpp)

#objs/game/generated/%.o: src/game/generated/%.cpp

other/icons/teeworlds_srv_gcc.coff:
	windres -i other/icons/teeworlds_srv_gcc.rc -o $@
other/icons/teeworlds_gcc.coff:
	windres -i other/icons/teeworlds_gcc.rc -o $@


