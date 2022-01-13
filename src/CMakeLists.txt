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
    events/arrangeMode/arrangeShips.c
    events/arrangeMode/drawArrangeShips.c
    events/attackMode/attackPlayer.c
    events/attackMode/drawAttackPlayer.c
    events/attackMode/drawSwitchAttackingPlayer.c
    events/attackMode/switchAttackingPlayer.c
    events/createMode/createPlayers.c
    events/createMode/drawCreatePlayers.c
    events/switchPlayer.c
    grid.c
    input.c
    player.c
    random.c
    ship.c
    vector.c
)

add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})