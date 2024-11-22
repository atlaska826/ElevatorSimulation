#include "elevator.h"
#include "floor.h"

// Constructor
Elevator::Elevator()
    : currentFloor(0), direction(0), capacity(0), numPassengers(0) {}

/*
 * =======
 * SETTERS
 * =======
 */

// Sets the elevator's current floor
void Elevator::setCurrentFloor(int cF) {
    currentFloor = cF;
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

// Returns the passengers in the elevator
std::vector<std::stack<Passenger>>& Elevator::getPassengers() {
    return passengers;
}

// Returns the set of destination floors
std::set<int>& Elevator::getDestinationFloors() {
    return destinationFloors;
}

/*
 * =================
 * CONTROL FUNCTIONS
 * =================
 */

// Adds a passenger to the elevator's stack
void Elevator::addPassenger(Passenger passenger) {
    int floor = passenger.destinationFloor;
    passengers[floor].push(passenger);
}

// Removes all the passengers for the giving floor
void Elevator::removePassengers(int floor) {
    while (!passengers[floor].empty()) {
        passengers[floor].pop();
    }
}

// Checks if the elevator is at capacity
bool Elevator::elevatorAtCapacity() const {
    return (numPassengers == capacity);
}

// Checks if the elevator is idle
bool Elevator::elevatorIsIdle() const {
    return (direction == 0);
}

// Add a floor to the destinationFloors set
void Elevator::addDestinationFloor(int floor) {
    destinationFloors.insert(floor);
}