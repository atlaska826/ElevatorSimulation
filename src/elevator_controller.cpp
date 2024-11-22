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
int ElevatorController::getCurrentTime() const {
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
 * ONBOARD QUEUE
 * =============
 */

// Adds a passenger to the onboard queue
void ElevatorController::addPassengerToOnboard(Passenger passenger) {
    onboardQueue.push(passenger);
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
    recordWaitTime(getCurrentTime() - passenger.requestTime);
    return passenger;
}

/*
 * ================
 * ELEVATOR CONTROL
 * ================
 */

// Adds a passenger to an elevator
// FIXME: You might be able to remove this
void ElevatorController::addPassengerToElevator(Elevator& elevator, Passenger passenger) {
    elevator.addPassenger(passenger);
}

// Clears the elevator for passengers of a specific floor
void ElevatorController::clearElevator(Elevator& elevator, int floor) {
    elevator.removePassengers(floor);
}

// Moves the elevator one floor
void ElevatorController::moveElevator(Elevator& elevator) {
    // TODO
    /*
     * IF elevator's floor queue is empty, don't move
     * ELSE-IF elevator's floor queue is not empty, move in direction of next floor
     */
}

/*
 * ============
 * SYSTEM LOGIC
 * ============
 */

// Handles passenger requests
void ElevatorController::processRequests() {
    while (!onboardQueue.empty()) {
        Passenger passenger = onboardQueue.front();
        Elevator* bestElevator = findBestElevator(passenger.destinationFloor);
        floors[passenger.initialFloor].addPassenger(passenger);
        bestElevator->setDestinationFloor(3); // FIXME: Add floor to best elevator's floor queue
        onboardQueue.pop();
    }
}

// Finds the elevator most optimal to pick up the passenger
Elevator* ElevatorController::findBestElevator(int floor) {
    Elevator* bestElevator = nullptr;
    int minScore = INT_MAX;

    // Score Values
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
                            (elevator->getCapacity() - elevator->getNumPassengers() > 3) ? 0 : HIGH_CAPACITY_PENALTY;

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