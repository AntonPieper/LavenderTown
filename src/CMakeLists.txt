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
    aabb.c
    cursor.c
    drawing.c
    events/arrangeShips.c
    events/createPlayers.c
    events/drawArrangeShips.c
    events/drawCreatePlayers.c
    grid.c
    input.c
    player.c
    random.c
    ship.c
    vector.c
)

add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})