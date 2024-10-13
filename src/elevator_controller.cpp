#include "elevator_controller.h"

// Constructor
ElevatorController::ElevatorController(int numFloors, int numElevators, int elevatorCapacity)
    : numFloors(numFloors), numElevators(numElevators), elevatorCapacity(elevatorCapacity), currentTime(0) {

    // Initialize elevator array
    elevators = new Elevator[numElevators];
    for (int i = 0; i < numElevators; ++i) {
        elevators[i].setCapacity(elevatorCapacity);
    }

    // Initialize floor map
    for (int i = 0; i < numFloors; ++i) {
        floors[i] = Floor();
    }
}

// Destructor
ElevatorController::~ElevatorController() {
    delete[] elevators;  // Free the dynamically allocated array
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

/*
 * =============
 * FLOOR CONTROL
 * =============
 */

// Adds a passenger to the waiting queue of a specified floor
void ElevatorController::addPassengerToFloor(int floor, Passenger passenger) {
    floors[floor].addPassenger(passenger);
}

// Gets the next passenger from a specified floor
Passenger ElevatorController::getPassengerFromFloor(int floor) {
    return floors[floor].getNextPassenger();
}