// COMSC-210 | Lab 32 | Mira Anand
// Module 12, Lesson: std::deque & std::stack, Assignment: Toll Booth
// IDE used: Visual Studio Code for Mac

#include "Car.h" // references the Car header file, which contains a class to create Car objects
#include <cstdlib> // needed to generate a random #
#include <ctime> // needed to generate a random #
#include <deque> // needed to use std::deque
#include <iostream>
using namespace std;

// declaration and initialization of global const int variables
const int INITIAL_LINE = 2; // represents the # of cars that are already in line to pay the toll when the simulation starts
const int HEAD_CAR_PAYS_LEAVES = 55; // represents the probability that the car at the head of the line pays its toll and leaves the toll booth
const int CAR_JOINS = 45; // represents the probability that another car will join the line for the toll booth

int main()
{
    srand(time(0)); // needed as the first line in main() in order to generate a random # for probability

    deque<Car> tollBoothLine; // create an std::deque that will hold Car objects

    int probability = rand() % 100 + 1; // generates a random # between 1-100 for probability
    int timePeriod = 1; // to keep track of the current time period

    // when the simulation starts, 2 cars should already be in line to pay the toll
    for (int i = 0; i < INITIAL_LINE; i++)
        tollBoothLine.push_back(Car()); // using .push_back() to add a Car object (using the Car class) to the back of the deque

    cout << "Initial queue:" << endl; // output the initial/starting queue of cars
    for (auto car : tollBoothLine) // using a range-based for loop and the "auto" keyword to output the contents of the std::deque
        car.print(); // using the .print() nethod in the Car class to print each Car object stored in the deque

    while (!tollBoothLine.empty()) // as long as the deque is not empty (.empty()) - meaning cars are still in line
    {
        cout << "Time: " << timePeriod << " "; // output the current time period

        if (probability <= HEAD_CAR_PAYS_LEAVES) // handle the case where the car at the head of the line pays & leaves
        {
            cout << "Operation: Car paid: ";
            // access the information of the head car by using .front() & print its info using .print() from the Car class
            // I am displaying the information first before using pop_back() so that I can access the car's information directly before removing it from the deque
            // the while loop performs a check to ensure that we will not rem
            tollBoothLine.front().print();
            tollBoothLine.pop_front(); // remove the head car from the deque by using .pop_front()
        }
    }
    
    return 0;
}