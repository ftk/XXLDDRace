aux_source_directory(. CLIENT_SRC)
aux_source_directory(./components CLIENT_SRC)
aux_source_directory(./.. CLIENT_SRC)
set(CLIENT_SRC
${CLIENT_SRC}
${GENERATED_FILES_PREFIX}/client_data.cpp
${GENERATED_FILES_PREFIX}/protocol.cpp
)

SET_SOURCE_FILES_PROPERTIES(${GENERATED_FILES_PREFIX}/client_data.cpp PROPERTIES GENERATED 1)
SET_SOURCE_FILES_PROPERTIES(${GENERATED_FILES_PREFIX}/protocol.cpp PROPERTIES GENERATED 1)
add_executable(teeworlds ${CLIENT_SRC})

target_link_libraries(teeworlds base engine-client editor json-parser)
install(TARGETS teeworlds DESTINATION ${TEEWORLDS_DESTINATION})
