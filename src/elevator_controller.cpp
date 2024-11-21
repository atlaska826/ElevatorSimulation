#include "elevator_controller.h"

// Constructor
ElevatorController::ElevatorController(int numFloors, int numElevators, int elevatorCapacity)
    : numFloors(numFloors), numElevators(numElevators), elevatorCapacity(elevatorCapacity), currentTime(0), totalWaitTime(0), totalPassengersServed(0) {

    // Initialize elevator array
    elevators = new Elevator[numElevators];
    for (int i = 0; i < numElevators; ++i) {
        elevators[i].setCapacity(elevatorCapacity);
    }

    // Initialize floor array
    floors = new Floor[numFloors];
}

// Destructor
ElevatorController::~ElevatorController() {
    // Free the dynamically allocated arrays
    delete[] elevators;
    delete[] floors;
}

/*
 * ============
 * TIME CONTROL
 * ============
 */

// Increments the time
void ElevatorController::incrementTime() {
    currentTime++;
}

// Gets the current time
int ElevatorController::getCurrentTime() {
    return currentTime;
}

// Adds passenger's wait time to the totalWaitTime
void ElevatorController::recordWaitTime(int waitTime) {
    totalWaitTime += waitTime;
}


// Calculates the total average wait time
double ElevatorController::calcAverageWaitTime() {
    if (totalPassengersServed == 0) {
        return 0.0;
    }
    return static_cast<double>(totalWaitTime) / totalPassengersServed;
}

/*
 * =============
 * FLOOR CONTROL
 * =============
 */

// Adds a passenger to the waiting queue of a specified floor
void ElevatorController::addPassengerToFloor(int floor, Passenger passenger) {
    floors[floor].addPassenger(passenger);
}

// Gets the next passenger from a specified floor and records the wait time
Passenger ElevatorController::getPassengerFromFloor(int floor) {
    Passenger passenger = floors[floor].getNextPassenger();
    recordWaitTime(passenger.pickupTime - passenger.requestTime);
    return passenger;
}

/*
 * ============
 * SYSTEM LOGIC
 * ============
 */

// TODO

/*
 * ================
 * ELEVATOR CONTROL
 * ================
 */

// TODO