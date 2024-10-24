#ifndef ELEVATORSIMULATION_ELEVATOR_H
#define ELEVATORSIMULATION_ELEVATOR_H

#include "Passenger.h"

#include <vector>
#include <stack>

class Elevator {
public:
    // Constructor
    Elevator();

    // Setters
    void setCurrentFloor(int cF);
    void setDestinationFloor(int dF);
    void setDirection(int d);
    void setCapacity(int c);
    void setNumPassengers(int n);

    // Getters
    int getCurrentFloor() const;
    int getDestinationFloor() const;
    int getDirection() const;
    int getCapacity() const;
    int getNumPassengers() const;

    // Control Functions
    bool elevatorAtCapacity();

private:
    std::vector<std::stack<Passenger>> passengers;
    int currentFloor;
    int destinationFloor;
    int direction;
    int capacity;
    int numPassengers;
};

#endif
