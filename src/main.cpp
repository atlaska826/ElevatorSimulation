#include "elevator_controller.h"

#include <iostream>

using namespace std;

int main() {
    int numFloors = 5;
    int numElevators = 1;
    int elevatorCapacity = 10;

    ElevatorController controller(numFloors, numElevators, elevatorCapacity);

    while (true) {
        controller.incrementTime();
        cout << controller.getCurrentTime() << endl;
        // TODO: Every second, add passengers and then run a process requests code in ElevatorController
        // TODO: Figure out what the stop conditions for the simulation are (either time or after a certain amount of passengers)
        // TODO: Output average waiting time
        break;
    }

    return 0;
}
