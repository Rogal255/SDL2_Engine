include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(ECS ECS.cpp)
target_link_libraries(ECS gtest_main)
