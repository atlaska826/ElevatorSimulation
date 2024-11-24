#include "simulation.h"

#include <iomanip>

/*
 * ==========
 * SIMULATION
 * ==========
 */

// Runs the whole simulation
void runSimulation(int& numPassengersTesting, int& passengersPerSec,
                   const int& numFloors, const int& numElevators, const int& elevatorCapacity) {
    srand(time(0));
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
        controller.updateElevators();
        controller.incrementTime();
    }

    outputSummary(controller);
}


/*
 * ==========
 * USER INPUT
 * ==========
 */

// Returns a valid integer input from user
int getIntegerFromUser(const string& inputPrompt, const int& maxValue) {
    int userInt;

    // Repeats question until valid response
    while (true) {
        cout << inputPrompt;
        cin >> userInt;

        // Checks for bad input
        if (cin.bad() || userInt < 1 || userInt > maxValue) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Your input must be a positive integer at or below " << maxValue << ".\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            return userInt;
        }
    }
}

// Gets the number of total passengers to test
int getNumTotalPassengers() {
    return getIntegerFromUser("Enter the total number of passengers to simulate (max 10000): ", 10000);
}

// Gets the number of passengers to simulate per second
int getPassengersPerSec() {
    return getIntegerFromUser("Enter the number of passengers to generate per second (max 30): ", 30);
}

// Gets the number of floors to simulate
int getNumFloors() {
    return getIntegerFromUser("Enter the number of floors in the simulation (max 150): ", 150);
}

// Gets the number of elevators to simulate
int getNumElevators() {
    return getIntegerFromUser("Enter the number of elevators to simulate (max 20): ", 20);
}

// Gets the capacity of the elevators
int getCapacity() {
    return getIntegerFromUser("Enter the capacity of each elevator (max 20): ", 20);
}

/*
 * ======
 * OUTPUT
 * ======
 */

// Output's current elevator data
void outputSummary(ElevatorController& controller) {
    cout << "=== SIMULATION RESULTS ===\n";
    cout << "Simulation Duration: " << controller.getCurrentTime() << " seconds" << endl;
    cout << "Total Passengers Served: " << controller.getTotalPassengersServed() << endl;
    cout << "Average Wait Time: " << fixed << setprecision(2) << controller.calcAverageWaitTime() << "s" << endl;
}
