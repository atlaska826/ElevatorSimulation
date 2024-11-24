#include "simulation.h"

int main() {
    cout << string(35, '-') << endl;
    cout << "=== ELEVATOR SIMULATION PROGRAM ===\n";
    cout << string(35, '-') << endl;

    // Simulation Setup
    int numTotalPassengers = getNumTotalPassengers();
    int passengersPerSec = getPassengersPerSec();
    const int numFloors = getNumFloors();
    const int numElevators = getNumElevators();
    const int elevatorCapacity = getCapacity();

    runSimulation(numTotalPassengers, passengersPerSec, numFloors, numElevators, elevatorCapacity);

    return 0;
}
