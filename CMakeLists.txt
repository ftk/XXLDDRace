project(teeworlds)
cmake_minimum_required(VERSION 2.8)

include(CPack)
#directory where teeworlds distributionwill be placed by default
set(TEEWORLDS_DESTINATION teeworlds)

#generating files location
set(GENERATED_FILES_PREFIX "${CMAKE_SOURCE_DIR}/src/game/generated")

#data dir installation
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION ${TEEWORLDS_DESTINATION})

#files installation
install(FILES ${CMAKE_SOURCE_DIR}/readme.txt 
    ${CMAKE_SOURCE_DIR}/storage.cfg
    DESTINATION ${TEEWORLDS_DESTINATION})

subdirs(datasrc src )
