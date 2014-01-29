aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SERVER_SRC)
aux_source_directory(./.. SERVER_SRC)
aux_source_directory(./gamemodes SERVER_SRC)
aux_source_directory(./entities SERVER_SRC)

set(SERVER_SRC
${SERVER_SRC}
${GENERATED_FILES_PREFIX}/server_data.cpp
${GENERATED_FILES_PREFIX}/protocol.cpp
)
SET_SOURCE_FILES_PROPERTIES(${GENERATED_FILES_PREFIX}/server_data.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(${GENERATED_FILES_PREFIX}/protocol.cpp PROPERTIES GENERATED 1)
add_executable(teeworlds_srv ${SERVER_SRC})
target_link_libraries(teeworlds_srv base engine-server)
install(TARGETS teeworlds_srv DESTINATION ${TEEWORLDS_DESTINATION})
