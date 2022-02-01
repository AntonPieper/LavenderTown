if(NOT APPLE)
    set(CURSES_NEED_WIDE true)
endif()

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

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

add_executable(LavenderTown ${SOURCES})

message(STATUS "Additional Curses Flags: \"${CURSES_CFlAGS}\"")

target_compile_options(LavenderTown PRIVATE ${CURSES_CFLAGS})

target_link_libraries(LavenderTown ${CURSES_LIBRARIES})

set_target_properties(LavenderTown
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PLATFORM}"
)