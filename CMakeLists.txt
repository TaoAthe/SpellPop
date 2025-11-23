cmake_minimum_required(VERSION 3.14)
project(SpellPop VERSION 0.9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)

file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)

add_executable(SpellPop ${SOURCES})

target_include_directories(SpellPop PRIVATE src)
target_link_libraries(SpellPop PRIVATE sfml-graphics sfml-audio sfml-network sfml-window sfml-system)

# Copy assets to build directory
add_custom_command(TARGET SpellPop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:SpellPop>/assets)

# Copy SFML DLLs to the executable directory
add_custom_command(TARGET SpellPop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE:sfml-network>
        $<TARGET_FILE_DIR:SpellPop>)
