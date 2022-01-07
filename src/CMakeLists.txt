set(SRC_LIST
        main.cpp
        TextureManager.cpp
        ContentManager.cpp
        Scene.cpp
        Game.cpp)

add_executable(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}-${CMAKE_BUILD_TYPE} PRIVATE ${SDL2main_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES})
add_custom_command(TARGET ${PROJECT_NAME}-${CMAKE_BUILD_TYPE}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}-${CMAKE_BUILD_TYPE}> ${CMAKE_SOURCE_DIR}/build)
