#ifndef ELEVATORSIMULATION_FLOOR_H
#define ELEVATORSIMULATION_FLOOR_H

#include "Passenger.h"
#include <queue>

class Floor {
private:
    std::queue<Passenger> waitingPassengers;

public:
    void addPassenger(Passenger passenger);
    Passenger getNextPassenger();
    bool hasWaitingPassengers() const;
};

#endif
