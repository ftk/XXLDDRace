#crapnet tool
add_executable(crapnet crapnet.cpp)
target_link_libraries(crapnet base)

#dilate tool
add_executable(dilate dilate.cpp)
target_link_libraries(dilate base pnglite ${ZLIB_LIBRARIES})

#fake_server tool
add_executable(fake_server fake_server.cpp)
target_link_libraries(fake_server engine-shared base )

#map_resave tool
add_executable(map_resave map_resave.cpp)
target_link_libraries(map_resave base engine-shared)

#map_version tool
add_executable(map_version map_version.cpp)
target_link_libraries(map_version base engine-shared)

#packetgen tool
add_executable(packetgen packetgen.cpp)
target_link_libraries(packetgen base)

#tileset_borderop tool
add_executable(tileset_borderop tileset_borderop.cpp)
target_link_libraries(tileset_borderop base pnglite ${ZLIB_LIBRARIES})
