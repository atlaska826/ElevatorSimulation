#ifndef ELEVATORSIMULATION_ELEVATOR_H
#define ELEVATORSIMULATION_ELEVATOR_H

#include "Passenger.h"

#include <list>

class Elevator {
public:
    // Constructor
    Elevator();

    // Setters
    void setCurrentFloor(int currentFloor);
    void setDestinationFloor(int destinationFloor);
    void setDirection(int direction);
    void setCapacity(int capacity);

    // Getters
    std::list<Passenger>& getPassengers();
    int getCurrentFloor() const;
    int getDestinationFloor() const;
    int getDirection() const;
    int getCapacity() const;

private:
    std::list<Passenger> passengers;
    int currentFloor;
    int destinationFloor;
    int direction;
    int capacity;
};

#endif
