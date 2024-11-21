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
    double calcAverageWaitTime() const;

    // Floor Control
    void addPassengerToFloor(int floor, Passenger passenger);
    Passenger getPassengerFromFloor(int floor);

    // System Logic
    void processRequest(Passenger passenger);
    Elevator* findBestElevator(int floor);

    // Elevator Control
    // TODO
    // Add passenger
    // Remove passenger
    // Move elevator

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