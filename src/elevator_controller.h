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
    int getCurrentTime() const;
    void recordWaitTime(int waitTime);
    double calcAverageWaitTime() const;

    // Floor Control
    void addPassengerToFloor(int floor, Passenger passenger);
    Passenger getPassengerFromFloor(int floor);

    // Elevator Control
    void addPassengerToElevator(Elevator& elevator, Passenger passenger);
    void clearElevator(Elevator& elevator, int floor);
    void moveElevator(Elevator& elevator);

    // System Logic
    void processRequests();
    Elevator* findBestElevator(int floor);

    // Onboard Queue
    void addPassengerToOnboard(Passenger passenger);

private:
    int numFloors;
    int numElevators;
    int elevatorCapacity;
    int currentTime;
    int totalWaitTime;
    int totalPassengersServed;
    Floor* floors;
    Elevator* elevators;
    std::queue<Passenger> onboardQueue;
};

#endif