#ifndef ELEVATORSIMULATION_ELEVATOR_H
#define ELEVATORSIMULATION_ELEVATOR_H

#include "passenger.h"

#include <vector>
#include <stack>
#include <set>

class Elevator {
public:
    // Constructor
    Elevator();

    // Setters
    void setCurrentFloor(int cF);
    void setDirection(int d);
    void setCapacity(int c);
    void setNumPassengers(int n);

    // Getters
    int getCurrentFloor() const;
    int getDirection() const;
    int getCapacity() const;
    int getNumPassengers() const;
    std::vector<std::stack<Passenger>>& getPassengers();
    std::set<int>& getDestinationFloors();

    // Control Functions
    void addPassenger(Passenger passenger);
    void removePassengers(int floor);
    bool elevatorAtCapacity() const;
    bool elevatorIsIdle() const;
    void addDestinationFloor(int floor);

private:
    std::vector<std::stack<Passenger>> passengers;
    std::set<int> destinationFloors;
    int currentFloor;
    int direction;
    int capacity;
    int numPassengers;
};

#endif
