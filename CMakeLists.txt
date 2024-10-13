cmake_minimum_required(VERSION 3.29)
project(ElevatorSimulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(ElevatorSimulation
        src/main.cpp
        src/elevator_controller.cpp
        src/elevator.cpp
        src/floor.cpp
)
