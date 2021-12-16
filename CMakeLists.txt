cmake_minimum_required(VERSION 3.10)

project(LavenderTown)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable (${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})