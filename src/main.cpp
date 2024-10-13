#include "elevator_controller.h"

using namespace std;

int main() {
    int numFloors = 5;
    int numElevators = 1;
    int elevatorCapacity = 10;

    ElevatorController controller(numFloors, numElevators, elevatorCapacity);

    return 0;
}
