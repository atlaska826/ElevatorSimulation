#ifndef ELEVATORSIMULATION_ELEVATOR_CONTROLLER_H
#define ELEVATORSIMULATION_ELEVATOR_CONTROLLER_H

#include "elevator.h"
#include "floor.h"

#include <map>

class ElevatorController {
public:
    // Constructor and Destructor
    ElevatorController(int numFloors, int numElevators, int elevatorCapacity);
    ~ElevatorController();

    // Time Control
    void incrementTime();
    int getCurrentTime();

    // Floor Control
    void addPassengerToFloor(int floor, Passenger passenger);
    Passenger getPassengerFromFloor(int floor);

private:
    int numFloors;
    int numElevators;
    int elevatorCapacity;
    int currentTime;
    std::map<int, Floor> floors;
    Elevator* elevators;
};

#endif