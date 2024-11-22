#ifndef ELEVATORSIMULATION_PASSENGER_H
#define ELEVATORSIMULATION_PASSENGER_H

struct Passenger {
    int initialFloor;
    int destinationFloor;
    int requestTime;

    Passenger(int initial, int destination, int reqTime)
        : initialFloor(initial), destinationFloor(destination), requestTime(reqTime) {}
};

#endif
