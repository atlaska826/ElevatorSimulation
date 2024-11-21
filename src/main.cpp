#include "elevator_controller.h"

#include <iostream>

using namespace std;

int main() {
    // Simulation Variables
    int numPassengersTesting = 100;
    const int numPassengersPerSec = 3;

    // Elevator Variables
    const int numFloors = 5;
    const int numElevators = 1;
    const int elevatorCapacity = 10;
    ElevatorController controller(numFloors, numElevators, elevatorCapacity);

    while (numPassengersTesting != 0) {
        controller.incrementTime();
        // TODO: Generate a number of passengers each second until numPassengers testing is at 0
        cout << controller.getCurrentTime() << " ";
        numPassengersTesting--;
    }

    cout << "\nAverage waiting time during simulation: " << controller.calcAverageWaitTime() << "s" << endl;
    return 0;
}
