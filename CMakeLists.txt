cmake_minimum_required(VERSION 3.14)
project(DeathRace VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Source files - all .cpp files in DeathRace/ directory
file(GLOB SOURCES "DeathRace/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib)

# Platform-specific linking
if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} winmm)
endif()

# Copy Content directory to build output
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/DeathRace/Content $<TARGET_FILE_DIR:${PROJECT_NAME}>/Content
)
