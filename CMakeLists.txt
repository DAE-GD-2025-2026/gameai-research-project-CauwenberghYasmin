cmake_minimum_required(VERSION 3.15)
project(gameai_research_project_CauwenberghYasmin)


cmake_policy(SET CMP0135 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(raylib)


add_executable(gameai_research_project_CauwenberghYasmin
        WaveFunctionCollapse/Main.cpp
        WaveFunctionCollapse/Tile.cpp
        WaveFunctionCollapse/Tile.h
)


target_include_directories(gameai_research_project_CauwenberghYasmin PRIVATE WaveFunctionCollapse)


target_link_libraries(gameai_research_project_CauwenberghYasmin raylib)


add_custom_command(TARGET gameai_research_project_CauwenberghYasmin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/WaveFunctionCollapse/Resources
        $<TARGET_FILE_DIR:gameai_research_project_CauwenberghYasmin>/Resources
)
