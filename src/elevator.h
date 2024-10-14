#ifndef ELEVATORSIMULATION_ELEVATOR_H
#define ELEVATORSIMULATION_ELEVATOR_H

#include "Passenger.h"

#include <list>

class Elevator {
public:
    // Constructor
    Elevator();

    // Setters
    void setCurrentFloor(int cF);
    void setDestinationFloor(int dF);
    void setDirection(int d);
    void setCapacity(int c);

    // Getters
    std::list<Passenger>& getPassengers();
    int getCurrentFloor() const;
    int getDestinationFloor() const;
    int getDirection() const;
    int getCapacity() const;

    // Control Functions
    bool elevatorAtCapacity();

private:
    std::list<Passenger> passengers;
    int currentFloor;
    int destinationFloor;
    int direction;
    int capacity;
};

#endif
