SET(SDL2_SEARCH_PATHS
        ${CMAKE_SOURCE_DIR}/lib/SDL2
        /usr
        )

FIND_LIBRARY(SDL2_image_LIBRARIES
        NAMES SDL2_image
        PATH_SUFFIXES lib lib/x86
        PATHS ${SDL2_SEARCH_PATHS}
        HINTS
        $ENV{SDL2DIR}
        )

INCLUDE(FindPackageHandleStandardArgs)
message("-- SDL2_image lib: " ${SDL2_image_LIBRARIES})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_image REQUIRED_VARS SDL2_image_LIBRARIES)