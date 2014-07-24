
srcs_to_objs = $(patsubst src/%.c,objs/%.o,$(patsubst src/%.cpp,objs/%.o,$(1)))
def_objs_var = $(1)_objs := $(call srcs_to_objs,$($(1)_srcs))
srcs_to_deps = $(patsubst src/%.c,objs/%.d,$(patsubst src/%.cpp,objs/%.d,$(1)))
def_deps_var = $(1)_deps := $(call srcs_to_deps,$($(1)_srcs))

# define source dirs and files


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


targets := client server versionsrv mastersrv banmaster

client_srcs := $(engine) $(client) $(game_shared) $(game_client) $(game_editor) $(zlib) $(wavpack) $(pnglite)
server_srcs := $(engine) $(server) $(game_shared) $(game_server) $(zlib) $(md5)
versionsrv_srcs := $(engine) $(versionsrv)
mastersrv_srcs := $(engine) $(mastersrv)
banmaster_srcs := $(engine) $(banmaster)

# define obj files and dep files

# client_objs = client_srcs (.cpp, .c -> .o)
$(foreach var,$(targets),$(eval $(call def_objs_var,$(strip $(var)))))
# client_deps = client_srcs (.cpp, .c -> .d)
$(foreach var,$(targets),$(eval $(call def_deps_var,$(strip $(var)))))

all_objs := $(sort $(foreach var,$(targets),$($(addsuffix _objs,$(var)))))
all_deps := $(sort $(foreach var,$(targets),$($(addsuffix _deps,$(var)))))


###

# prereqs for all objs
# mkdir if needed
.SECONDEXPANSION:
$(all_objs): $(generated_h) | $$(dir $$@)

# rules for obj dirs
$(sort $(dir $(all_objs))):
	mkdir -p '$@'



# rules for generating source and headers

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

# light
#objs/%.o: src/%.c
#	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o '$@' '$<'

# pro (generate dependencies)
objs/%.o: src/%.c
	$(CC) -MMD -MP -c $(CPPFLAGS) $(CFLAGS) -o '$@' '$<'
objs/%.o: src/%.cpp
	$(CXX) -MMD -MP -c $(CPPFLAGS) $(CXXFLAGS) -o '$@' '$<'

# dependencies for source files

ifndef fast
-include $(all_deps)
endif
