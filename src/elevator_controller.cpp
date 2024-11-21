#include "elevator_controller.h"

#include <iostream> // TODO: Remove later once you are done with debugging

// Constructor
ElevatorController::ElevatorController(int numFloors, int numElevators, int elevatorCapacity)
    : numFloors(numFloors), numElevators(numElevators), elevatorCapacity(elevatorCapacity), currentTime(0), totalWaitTime(0), totalPassengersServed(0) {

    // Initialize elevator array
    elevators = new Elevator[numElevators];
    for (int i = 0; i < numElevators; ++i) {
        elevators[i].setCapacity(elevatorCapacity);
    }

    // Initialize floor array
    floors = new Floor[numFloors];
}

// Destructor
ElevatorController::~ElevatorController() {
    // Free the dynamically allocated arrays
    delete[] elevators;
    delete[] floors;
}

/*
 * ============
 * TIME CONTROL
 * ============
 */

// Increments the time
void ElevatorController::incrementTime() {
    currentTime++;
}

// Gets the current time
int ElevatorController::getCurrentTime() {
    return currentTime;
}

// Adds passenger's wait time to the totalWaitTime
void ElevatorController::recordWaitTime(int waitTime) {
    totalWaitTime += waitTime;
}


// Calculates the total average wait time
double ElevatorController::calcAverageWaitTime() const {
    if (totalPassengersServed == 0) {
        return 0.0;
    }
    return static_cast<double>(totalWaitTime) / totalPassengersServed;
}

/*
 * =============
 * FLOOR CONTROL
 * =============
 */

// Adds a passenger to the waiting queue of a specified floor
void ElevatorController::addPassengerToFloor(int floor, Passenger passenger) {
    floors[floor].addPassenger(passenger);
}

// Gets the next passenger from a specified floor and records the wait time
Passenger ElevatorController::getPassengerFromFloor(int floor) {
    Passenger passenger = floors[floor].getNextPassenger();
    recordWaitTime(passenger.pickupTime - passenger.requestTime);
    return passenger;
}

/*
 * ============
 * SYSTEM LOGIC
 * ============
 */

// Finds the elevator most optimal to pick up the passenger
Elevator* ElevatorController::findBestElevator(int floor) {
    Elevator* bestElevator = nullptr;
    int minScore = INT_MAX;

    const int FULL_CAPACITY_PENALTY = 20;
    const int HIGH_CAPACITY_PENALTY = 5;
    const int WRONG_DIRECTION_PENALTY = 10;
    const int IDLE_BONUS = -5;

    for (int i = 0; i < numElevators; ++i) {
        Elevator* elevator = &elevators[i];

        // Immediately returns elevator if it is idle and at the request floor
        if (elevator->getDirection() == 0 && elevator->getCurrentFloor() == floor) {
            // FIXME: Turn on once finished with debugging
            //return elevator;
        }

        // Capacity Score: Favors elevators with open space
        int capacityScore = (elevator->elevatorAtCapacity()) ? FULL_CAPACITY_PENALTY :
                            (elevator->getCapacity() - elevator->getNumPassengers() > 1) ? 0 : HIGH_CAPACITY_PENALTY;

        // Direction Score: Favors elevators that are idle (best) or moving in the same direction the floor is
        int directionScore;
        if (elevator->getDirection() == 0) {
            directionScore = IDLE_BONUS;
        } else if ((elevator->getDirection() == 1 && floor > elevator->getCurrentFloor()) ||
                    (elevator->getDirection() == -1 && floor < elevator->getCurrentFloor())) {
            directionScore = 0;
        } else {
            directionScore = WRONG_DIRECTION_PENALTY;
        }

        // Proximity Score: Favors elevators closest to the request floor
        int proximityScore = abs(elevator->getCurrentFloor() - floor);

        // Total Score: Calculates the total score and checks to see if the elevator is the best
        int totalScore = capacityScore + directionScore + proximityScore;
        if (totalScore < minScore) {
            minScore = totalScore;
            bestElevator = elevator;
        }

        // TODO: Remove debugging once finished
        std::cout << "Elevator " << i << " - Capacity: " << capacityScore
          << ", Direction: " << directionScore
          << ", Proximity: " << proximityScore
          << ", Total: " << totalScore << "\n";
    }
    return bestElevator;
}

/*
 * ================
 * ELEVATOR CONTROL
 * ================
 */

// TODO