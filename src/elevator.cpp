#include "elevator.h"

// Constructor
Elevator::Elevator()
    : currentFloor(0), destinationFloor(0), direction(0), capacity(0), numPassengers(0) {}

/*
 * =======
 * SETTERS
 * =======
 */

// Sets the elevator's current floor
void Elevator::setCurrentFloor(int cF) {
    currentFloor = cF;
}

// Sets the elevator's destination floor
void Elevator::setDestinationFloor(int dF) {
    destinationFloor = dF;
}

// Sets the elevator's direction
void Elevator::setDirection(int d) {
    direction = d;
}

// Sets the elevator's capacity
void Elevator::setCapacity(int c) {
    capacity = c;
}

// Sets the number of passengers in the elevator
void Elevator::setNumPassengers(int n) {
    numPassengers = n;
}

/*
 * =======
 * GETTERS
 * =======
 */

// Gets the elevator's current floor
int Elevator::getCurrentFloor() const {
    return currentFloor;
}

// Gets the elevator's destination floor
int Elevator::getDestinationFloor() const {
    return destinationFloor;
}

// Gets the elevator's direction
int Elevator::getDirection() const {
    return direction;
}

// Gets the elevator's capacity
int Elevator::getCapacity() const {
    return capacity;
}

// Gets the number of passengers in the elevator
int Elevator::getNumPassengers() const {
    return numPassengers;
}

/*
 * =================
 * CONTROL FUNCTIONS
 * =================
 */

// Checks if the elevator is at capacity
bool Elevator::elevatorAtCapacity() {
    return (numPassengers == capacity);
}