aux_source_directory(. VERSIONSRV_SRC)
add_executable(versionsrv ${VERSIONSRV_SRC})
target_link_libraries(versionsrv base engine-shared)
