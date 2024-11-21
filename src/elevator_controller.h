#ifndef ELEVATORSIMULATION_ELEVATOR_CONTROLLER_H
#define ELEVATORSIMULATION_ELEVATOR_CONTROLLER_H

#include "elevator.h"
#include "floor.h"

class ElevatorController {
public:
    // Constructor and Destructor
    ElevatorController(int numFloors, int numElevators, int elevatorCapacity);
    ~ElevatorController();

    // Time Control
    void incrementTime();
    int getCurrentTime();
    void recordWaitTime(int waitTime);
    double calcAverageWaitTime();

    // Floor Control
    void addPassengerToFloor(int floor, Passenger passenger);
    Passenger getPassengerFromFloor(int floor);

    // System Logic
    // TODO

    // Elevator Control
    // TODO: Process requests
    Elevator* findBestElevator(int floor);

private:
    int numFloors;
    int numElevators;
    int elevatorCapacity;
    int currentTime;
    int totalWaitTime;
    int totalPassengersServed;
    Floor* floors;
    Elevator* elevators;
};

#endif