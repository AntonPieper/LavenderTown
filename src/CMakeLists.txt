if(UNIX)
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
else(WIN32)
    include_directories(${PROJECT_NAME} PRIVATE ${LavenderTown_SOURCE_DIR}/include)
    link_directories(${LavenderTown_SOURCE_DIR}/lib)
    set(CURSES_LIBRARIES pdcurses)
endif(UNIX)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES
    main.c
    grid.c
    random.c
    vector.c
    ship.c
    aabb.c
)

add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})