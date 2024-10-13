#include "floor.h"

// Adds a passenger to the queue
void Floor::addPassenger(Passenger passenger) {
    waitingPassengers.push(passenger);
}

// Removes and returns the next passenger in line
Passenger Floor::getNextPassenger() {
    Passenger nextPassenger = waitingPassengers.front();
    waitingPassengers.pop();
    return nextPassenger;
}

// Checks if the floor has any waiting passengers
bool Floor::hasWaitingPassengers() const {
    return !waitingPassengers.empty();
}