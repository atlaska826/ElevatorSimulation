#ifndef ELEVATORSIMULATION_PASSENGER_H
#define ELEVATORSIMULATION_PASSENGER_H

struct Passenger {
    int initialFloor;
    int destinationFloor;
    int direction;
    int timeEntered;

    Passenger(int initial, int destination, int direct, int time)
        : initialFloor(initial), destinationFloor(destination), direction(direct), timeEntered(time) {}
};

#endif
