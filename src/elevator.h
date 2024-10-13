#ifndef ELEVATORSIMULATION_ELEVATOR_H
#define ELEVATORSIMULATION_ELEVATOR_H

#include <queue>

struct Passenger {
    int initialFloor;
    int destinationFloor;
    int direction;
    int timeEntered;

    Passenger(int initial, int destination, int direct, int time)
        : initialFloor(initial), destinationFloor(destination), direction(direct), timeEntered(time) {}
};

class Elevator {
private:
    std::queue<Passenger> elevatorQueue;
    int initialFloor;
    int destinationFloor; // May remove this later
    int direction;
    int numPassengers;
    int capacity; // May remove this later
};


#endif
