aux_source_directory(. ENGINE_SERVER_SRC)
add_library(engine-server ${ENGINE_SERVER_SRC})
target_link_libraries(engine-server engine-shared)
