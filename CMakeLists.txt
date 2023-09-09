cmake_minimum_required(VERSION 3.22)
project(chip8_emulator C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(libs/SDL2/include)
link_directories(libs/SDL2/lib/x64)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)