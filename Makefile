ARCH ?= 64
CPPFLAGS := -m$(ARCH) -flto -O3 -mfpmath=both -mavx -mpclmul -pipe -fno-exceptions -fvisibility=internal \
-Wall -DCONF_RELEASE -DNO_VIZ -I "src" -I "other/mysql/include" -I "src/engine/external/zlib" -I "other/sdl/include" -I "other/freetype/include"
CXXFLAGS := -std=c++11 -fno-rtti
CFLAGS :=
LDFLAGS := -m$(ARCH) -flto -O3 -s -static-libgcc -static-libstdc++

CC := gcc
CXX := g++
LD := $(CXX)
PYTHON ?= python
WINDRES ?= windres

srcs_to_objs = $(patsubst src/%.c,objs/%.o,$(patsubst src/%.cpp,objs/%.o,$(1)))
def_objs_var = $(1)_objs := $(call srcs_to_objs,$($(1)_srcs))


headers := $(wildcard src/engine/external/wavpack/*.h src/engine/external/zlib/*.h src/engine/external/pnglite/*.h src/engine/external/md5/*.h src/engine/shared/*.h src/base/*.h src/base/tl/*.h src/game/*.h)

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



targets := client server versionsrv mastersrv banmaster

client_srcs := $(engine) $(client) $(game_shared) $(game_client) $(game_editor) $(zlib) $(wavpack) $(pnglite)
server_srcs := $(engine) $(server) $(game_shared) $(game_server) $(zlib) $(md5)
versionsrv_srcs := $(engine) $(versionsrv)
mastersrv_srcs := $(engine) $(mastersrv)
banmaster_srcs := $(engine) $(banmaster)


# client_objs = client_srcs (.cpp, .c -> .o)
$(foreach var,$(targets),$(eval $(call def_objs_var,$(strip $(var)))))

all_objs := $(foreach var,$(targets),$($(addsuffix _objs,$(var))))

all: XXLDDRace.exe XXLDDRace-Server.exe versionsrv.exe mastersrv.exe banmaster.exe

XXLDDRace.exe: $(client_objs) other/icons/teeworlds_gcc.coff
	$(LD) $(LDFLAGS) -o '$@' $^ -Lother/sdl/lib$(ARCH) -Lother/freetype/lib$(ARCH) -lws2_32 -lgdi32 -lopengl32 -lglu32 -lfreetype -lSDL -lSDLmain

XXLDDRace-Server.exe: $(server_objs) other/icons/teeworlds_srv_gcc.coff
	$(LD) $(LDFLAGS) -o '$@' $^ -lws2_32

#versionsrv.exe: $(versionsrv_objs)
#	$(LD) $(LDFLAGS) -o '$@' $^ -lws2_32
#mastersrv.exe: $(mastersrv_objs)
#	$(LD) $(LDFLAGS) -o '$@' $^ -lws2_32
#banmaster.exe: $(banmaster_objs)
#	$(LD) $(LDFLAGS) -o '$@' $^ -lws2_32
.SECONDEXPANSION:
versionsrv.exe mastersrv.exe banmaster.exe: $$($$(patsubst %.exe,%_objs,$$@))
	$(LD) $(LDFLAGS) -o '$@' $^ -lws2_32


# all objs depend on headers
$(all_objs): $(generated_h) $(headers)

clean:
	-rm $(sort $(all_objs) XXLDDRace.exe XXLDDRace-Server.exe $(generated) )

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

# rules for c, cpp files
objs/%.o: src/%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o '$@' '$<'
objs/%.o: src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) -o '$@' '$<'

%.coff: %.rc
	$(WINDRES) -i $< -o $@



.PHONY: all clean
