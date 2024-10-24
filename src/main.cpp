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
        break;
    }

    return 0;
}
