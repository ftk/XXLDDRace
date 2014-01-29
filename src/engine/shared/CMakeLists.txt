aux_source_directory(. ENGINE_SHARED_SRC)
add_library(engine-shared ${ENGINE_SHARED_SRC})
target_link_libraries(engine-shared ${ZLIB_LIBRARIES})
