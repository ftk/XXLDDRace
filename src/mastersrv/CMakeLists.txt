aux_source_directory(. MASTERSRV_SRC)
add_executable(mastersrv ${MASTERSRV_SRC})
target_link_libraries(mastersrv base engine-shared)
