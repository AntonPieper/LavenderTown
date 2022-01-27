find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES
    main.c
    cursor.c
    events/arrangeMode/arrangeShips.c
    events/arrangeMode/drawArrangeShips.c
    events/attackMode/attackPlayer.c
    events/attackMode/drawAttackPlayer.c
    events/attackMode/drawSwitchAttackingPlayer.c
    events/attackMode/switchAttackingPlayer.c
    events/createMode/createPlayers.c
    events/createMode/drawCreatePlayers.c
    events/switchPlayer.c
    events/endScreen/endScreen.c
    grid.c
    input.c
    player.c
    ship.c
    util/aabb.c
    util/drawing.c
    util/random.c
    util/vector.c
    windows.c
)

add_executable (${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})