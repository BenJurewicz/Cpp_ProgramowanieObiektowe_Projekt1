cmake_minimum_required(VERSION 3.22)
project(Projekt1Cpp)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Projekt1Cpp main.cpp
        world.cpp
        world.h
        creatures/creature.cpp
        creatures/creature.h
        creatures/animals/animal.cpp
        creatures/animals/animal.h
        creatures/plants/plant.cpp
        creatures/plants/plant.h
        console.cpp
        console.h
        Point.cpp
        Point.h
        creatures/animals/human.cpp
        creatures/animals/human.h
        creatures/animals/wolf.cpp
        creatures/animals/wolf.h
        rng.cpp
        rng.h
        creatures/animals/sheep.cpp
        creatures/animals/sheep.h
        log.cpp
        log.h
)

target_link_libraries(Projekt1Cpp ${CURSES_LIBRARIES})