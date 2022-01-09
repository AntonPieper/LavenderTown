cmake_minimum_required(VERSION 3.10)

project(LavenderTown)
if(EXISTS ${CMAKE_SOURCE_DIR}/.clangd.in)
    configure_file(.clangd.in ${CMAKE_SOURCE_DIR}/.clangd @ONLY)
endif()

add_subdirectory(src)
