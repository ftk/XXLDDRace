include_directories(.)
find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
endif( ZLIB_FOUND )

find_package( SDL REQUIRED )
if ( SDL_FOUND )
    include_directories( ${SDL_INCLUDE_DIR} )
endif( SDL_FOUND )

subdirs(versionsrv base engine game mastersrv tools)
