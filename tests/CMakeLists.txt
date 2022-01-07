include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(General_ECS_ut-${CMAKE_BUILD_TYPE} ECS.cpp
        ../src/ContentManager.cpp
        ../src/Scene.cpp)

target_link_libraries(General_ECS_ut-${CMAKE_BUILD_TYPE} gtest_main)

add_custom_command(TARGET General_ECS_ut-${CMAKE_BUILD_TYPE}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:General_ECS_ut-${CMAKE_BUILD_TYPE}> ${CMAKE_SOURCE_DIR}/build)
