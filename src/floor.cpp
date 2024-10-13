#include "floor.h"

void Floor::addPassenger(Passenger passenger) {
    waitingPassengers.push(passenger);
}

Passenger Floor::getNextPassenger() {
    Passenger nextPassenger = waitingPassengers.front();
    waitingPassengers.pop();
    return nextPassenger;
}

bool Floor::hasWaitingPassengers() const {
    return !waitingPassengers.empty();
}