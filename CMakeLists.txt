cmake_minimum_required(VERSION 3.22)
project(Projekt1Cpp)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Projekt1Cpp main.cpp
        world.cpp
        world.h
        creature.cpp
        creature.h
        animal.cpp
        animal.h
        plant.cpp
        plant.h
        console.cpp
        console.h
)

target_link_libraries(Projekt1Cpp ${CURSES_LIBRARIES})