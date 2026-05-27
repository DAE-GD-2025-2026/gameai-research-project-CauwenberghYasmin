cmake_minimum_required(VERSION 3.15)
project(gameai_research_project_CauwenberghYasmin)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# 1. Fetch the ACTUAL Raylib library from its official source
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG v4.0
)
FetchContent_MakeAvailable(raylib)

# 2. Define your executable using your exact assignment name
add_executable(gameai_research_project_CauwenberghYasmin
        WaveFunctionCollapse/Main.cpp
        WaveFunctionCollapse/Tile.cpp
        WaveFunctionCollapse/Tile.h
)

# 3. Tell the compiler where to look for your header files
target_include_directories(gameai_research_project_CauwenberghYasmin PRIVATE WaveFunctionCollapse)

# 4. Link Raylib to your project
target_link_libraries(gameai_research_project_CauwenberghYasmin raylib)

# 5. Copy your Resources folder to the build directory
add_custom_command(TARGET gameai_research_project_CauwenberghYasmin POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/WaveFunctionCollapse/Resources
        $<TARGET_FILE_DIR:gameai_research_project_CauwenberghYasmin>/Resources
)
