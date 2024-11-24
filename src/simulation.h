#ifndef ELEVATORSIMULATION_SIMULATION_H
#define ELEVATORSIMULATION_SIMULATION_H

#include "elevator_controller.h"

#include <iostream>
using namespace std;

// Simulation
void runSimulation(int& numPassengersTesting, int& passengersPerSec,
                   const int& numFloors, const int& numElevators, const int& elevatorCapacity);

// User Input
int getIntegerFromUser(const string& inputPrompt, const int& maxValue);
int getNumTotalPassengers();
int getPassengersPerSec();
int getNumFloors();
int getNumElevators();
int getCapacity();

// Output
void outputSummary(ElevatorController& controller);

#endif
