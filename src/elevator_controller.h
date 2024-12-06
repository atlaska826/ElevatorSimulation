#ifndef ELEVATORSIMULATION_ELEVATOR_CONTROLLER_H
#define ELEVATORSIMULATION_ELEVATOR_CONTROLLER_H

#include "elevator.h"
#include "floor.h"

class ElevatorController {
public:
    // Constructor and Destructor
    ElevatorController(int numFloors, int numElevators, int elevatorCapacity);
    ~ElevatorController();

    // Getters
    Elevator* getElevators();
    int getTotalPassengersServed();

    // Time Control
    void incrementTime();
    int getCurrentTime() const;
    void recordWaitTime(int waitTime);
    double calcAverageWaitTime() const;

    // Onboard Queue
    void addPassengerToOnboard(Passenger passenger);

    // System Logic
    void processRequests();
    Elevator* findBestElevator(int floor);
    void updateElevators();

    // System Control
    Passenger getPassengerFromFloor(int floor);
    void addPassengerToElevator(Elevator& elevator, Passenger passenger);
    void getNextDestinationFloor(Elevator& currentElevator, int currentFloor);

private:
    Floor* floors;
    Elevator* elevators;
    std::queue<Passenger> onboardQueue;
    int numFloors;
    int numElevators;
    int elevatorCapacity;
    int currentTime;
    int totalWaitTime;
    int totalPassengersServed;
};

#endif