#include "elevator_controller.h"

#include <iostream> // TODO: Remove later once you are done with debugging

// Constructor
ElevatorController::ElevatorController(int numFloors, int numElevators, int elevatorCapacity)
    : numFloors(numFloors), numElevators(numElevators), elevatorCapacity(elevatorCapacity), currentTime(0), totalWaitTime(0), totalPassengersServed(0) {

    // Initialize elevator array and elevator passenger stacks
    elevators = new Elevator[numElevators];
    for (int i = 0; i < numElevators; ++i) {
        elevators[i].setCapacity(elevatorCapacity);
        elevators[i].initializePassengers(numFloors);
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
void ElevatorController::addPassengerToElevator(Elevator& elevator, Passenger passenger) {
    elevator.addPassenger(passenger);
}

// Manages the destination floor and directional state for each elevator
void ElevatorController::getNextDestinationFloor(Elevator& elevator, int floor) {
    std::set<int>& destinationFloors = elevator.getDestinationFloors();
    int nextFloor = floor;

    // Sets direction to idle if elevator has no destination floors
    if (destinationFloors.empty()) {
        elevator.setDirection(0);
        return;
    }

    // Elevator is idle
    if (elevator.getDirection() == 0) {
        // Find the smallest floor greater than or equal to the current floor
        auto checkItr = destinationFloors.lower_bound(floor);

        // If a valid floor is found above or at the current floor
        if (checkItr != destinationFloors.end()) {
            nextFloor = *checkItr;
            elevator.setDirection(1); // Set direction to up
        } else {
            // Go to the next largest floor below the current one
            nextFloor = *std::prev(destinationFloors.end());
            elevator.setDirection(-1);
        }

        // Remove the curren floor from the destinations set
        destinationFloors.erase(nextFloor);
    }

    // Elevator is moving up
    else if (elevator.getDirection() > 0) {
        // Find the smallest floor greater than or equal to the current floor
        auto itr = destinationFloors.lower_bound(floor);

        // If a valid floor is found above or at the current floor
        if (itr != destinationFloors.end()) {
            nextFloor = *itr;
            destinationFloors.erase(itr);
        } else {
            // Switch direction if no higher floors exist
            elevator.setDirection(-1);
            if (!destinationFloors.empty()) { // Error check
                nextFloor = *std::prev(destinationFloors.end());
                destinationFloors.erase(std::prev(destinationFloors.end()));
            }
        }
    }

    // Elevator is moving down
    else if (elevator.getDirection() < 0) {
        // Find the first floor below the current floor
        auto itr = destinationFloors.upper_bound(floor);

        // If a valid floor below the current floor exists
        if (itr != destinationFloors.begin()) {
            --itr;
            nextFloor = *itr;
            destinationFloors.erase(itr);
        } else {
            // Switch direction if no lower floors exist
            elevator.setDirection(1);
            if (!destinationFloors.empty()) {
                nextFloor = *destinationFloors.begin();
                destinationFloors.erase(destinationFloors.begin());
            }
        }
    }

    // Set the elevator's current floor and output information
    elevator.setCurrentFloor(nextFloor);
    std::cout << "Elevator at floor " << floor
              << " heading to floor " << elevator.getCurrentFloor()
              << " with " << elevator.getNumPassengers() << " passengers." << std::endl;
}

// Runs the elevator's movements
void ElevatorController::updateElevators() {
    for (int i = 0; i < numElevators; ++i) {
        Elevator& currentElevator = elevators[i];
        int currentFloor = currentElevator.getCurrentFloor();
        std::vector<std::stack<Passenger>>& passengers = currentElevator.getPassengers();

        // Disembark passengers getting off at the current floor
        if (currentFloor < passengers.size() && !passengers[currentFloor].empty()) {
            currentElevator.removePassengers(currentFloor);
        }

        // Board passengers from the current floor
        while (!currentElevator.elevatorAtCapacity() && floors[currentFloor].hasWaitingPassengers()) {
            Passenger passenger = getPassengerFromFloor(currentFloor);
            addPassengerToElevator(currentElevator, passenger);
        }

        // Update the elevator's destination
        getNextDestinationFloor(currentElevator, currentFloor);
    }
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
        onboardQueue.pop();

        floors[passenger.initialFloor].addPassenger(passenger);
        Elevator* bestElevator = findBestElevator(passenger.destinationFloor);
        bestElevator->addDestinationFloor(passenger.destinationFloor);

        if (bestElevator->elevatorIsIdle()) {
            bestElevator->setDirection(passenger.destinationFloor > bestElevator->getCurrentFloor() ? 1 : -1);
        }

        totalPassengersServed++;
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
        if (elevator->elevatorIsIdle() == 0 && elevator->getCurrentFloor() == floor) {
            return elevator;
        }

        // Capacity Score: Favors elevators with open space
        int capacityScore = (elevator->elevatorAtCapacity()) ? FULL_CAPACITY_PENALTY :
                            (elevator->getCapacity() - elevator->getNumPassengers() > 3) ? 0 : HIGH_CAPACITY_PENALTY;

        // Direction Score: Favors elevators that are idle (best) or moving in the same direction the floor is
        int directionScore;
        if (elevator->elevatorIsIdle()) {
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
    }
    return bestElevator;
}