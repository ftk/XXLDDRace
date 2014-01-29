find_package(Freetype REQUIRED)
if(FREETYPE_FOUND)
include_directories(${FREETYPE_INCLUDE_DIRS})
endif(FREETYPE_FOUND)

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
include_directories(OPENGL_INCLUDE_DIR)
endif(OPENGL_FOUND)

aux_source_directory(. ENGINE_CLIENT_SRC)

add_library(engine-client ${ENGINE_CLIENT_SRC})

target_link_libraries(engine-client
engine-shared
wavpack
pnglite
${OPENGL_LIBRARIES}
${SDL_LIBRARY}
${FREETYPE_LIBRARIES}
)
