#include "elevator_controller.h"
#include "passenger.h"

#include <iostream>

using namespace std;

int main() {
    // Simulation Variables
    //srand(time(0));
    srand(0);
    int numPassengersTesting = 100;
    int passengersPerSec = 2;

    // Elevator Variables
    const int numFloors = 5;
    const int numElevators = 1;
    const int elevatorCapacity = 15;
    ElevatorController controller(numFloors, numElevators, elevatorCapacity);

    // Passenger Variables
    int initialFloor;
    int destinationFloor;

    while (numPassengersTesting != 0) {
        // Don't test more passengers than wanted by the user
        if (numPassengersTesting < passengersPerSec) {
            passengersPerSec = numPassengersTesting;
        }

        for (int i = 0; i < passengersPerSec; ++i) {
            // Random start floor
            initialFloor = rand() % numFloors;

            // Random destination floor
            destinationFloor = rand() % numFloors;
            while (initialFloor == destinationFloor) {
                destinationFloor = rand() % numFloors;
            }

            Passenger passenger(initialFloor, destinationFloor, controller.getCurrentTime());
            controller.addPassengerToOnboard(passenger);
        }
        numPassengersTesting -= passengersPerSec;
        controller.processRequests();
        controller.incrementTime();
    }

    cout << "\nAverage waiting time during simulation: " << controller.calcAverageWaitTime() << "s" << endl;
    return 0;
}
