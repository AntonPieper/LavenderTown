cmake_minimum_required(VERSION 3.10)

project(LavenderTown)

if(UNIX)
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
else(WIN32)
    set(PDCURSES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/PDCurses")
    include_directories(${PDCURSES_PATH})
    find_library(PDCURSES_LIB NAMES pdcurses HINTS ${PDCURSES_PATH}/wincon)
    set(CURSES_LIBRARIES ${PDCURSES_LIB})
endif(UNIX)

add_executable (${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})