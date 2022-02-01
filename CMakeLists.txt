cmake_minimum_required(VERSION 3.10)

project(LavenderTown-linux-arm64 C)

option(MACOS_UNIVERSAL "MACOS_UNIVERSAL" OFF)

if(MACOS_UNIVERSAL)
    set(CMAKE_OSX_ARCHITECTURES arm64 x86_64)
endif()

string(TOLOWER ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR} PLATFORM)

if(${CMAKE_SYSTEM_NAME} MATCHES Darwin AND CMAKE_OSX_ARCHITECTURES MATCHES "arm64;x86_64")
    set(PLATFORM darwin-universal)
endif()

add_subdirectory(src)
