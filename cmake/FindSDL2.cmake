SET(SDL2_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/lib/SDL2
        /usr
        )

FIND_PATH(SDL2_INCLUDE_DIRS SDL.h
        PATH_SUFFIXES include include/SDL2
        PATHS ${SDL2_SEARCH_PATHS}
        HINTS
        $ENV{SDL2DIR}
        )

FIND_LIBRARY(SDL2_LIBRARIES
        NAMES SDL2
        PATH_SUFFIXES lib lib/x86
        PATHS ${SDL2_SEARCH_PATHS}
        HINTS
        $ENV{SDL2DIR}
        )

INCLUDE(FindPackageHandleStandardArgs)
message("-- SDL2 include dir: " ${SDL2_INCLUDE_DIRS})
message("-- SDL2 lib: " ${SDL2_LIBRARIES})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2 REQUIRED_VARS SDL2_LIBRARIES SDL2_INCLUDE_DIRS)
