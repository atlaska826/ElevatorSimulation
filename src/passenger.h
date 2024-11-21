#ifndef ELEVATORSIMULATION_PASSENGER_H
#define ELEVATORSIMULATION_PASSENGER_H

struct Passenger {
    int initialFloor;
    int destinationFloor;
    int direction;
    int requestTime;
    int pickupTime;

    Passenger(int initial, int destination, int direct, int reqTime, int pickTime)
        : initialFloor(initial), destinationFloor(destination), direction(direct), requestTime(reqTime), pickupTime(pickTime) {}
};

#endif
