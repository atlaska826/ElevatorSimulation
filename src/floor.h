#ifndef ELEVATORSIMULATION_FLOOR_H
#define ELEVATORSIMULATION_FLOOR_H

#include "Passenger.h"

#include <queue>

class Floor {
public:
    // Adds a passenger to the queue
    void addPassenger(Passenger passenger);

    // Removes and returns the next passenger in line
    Passenger getNextPassenger();

    // Checks if the floor has any waiting passengers
    bool hasWaitingPassengers() const;

private:
    // Queue of all passengers waiting on the floor
    std::queue<Passenger> waitingPassengers;
};

#endif
