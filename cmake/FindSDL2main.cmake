SET(SDL2_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/lib/SDL2
        /usr
        )

FIND_LIBRARY(SDL2main_LIBRARIES
        NAMES SDL2main
        PATH_SUFFIXES lib lib/x86
        PATHS ${SDL2_SEARCH_PATHS}
        HINTS
        $ENV{SDL2DIR}
        )

INCLUDE(FindPackageHandleStandardArgs)
message("-- SDL2main lib: " ${SDL2main_LIBRARIES})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2main REQUIRED_VARS SDL2main_LIBRARIES)