// COMSC-210 | Lab 33 | Mira Anand
// Module 12, Lesson: std::deque & std::stack, Assignment: Toll Plaza
// IDE used: Visual Studio Code for Mac

// To see coding progression for Lab #32, please see the "main" branch on GitHub
// To see coding progression for Lab #33, please see the "lab33" branch on GitHub

#include "Car.h" // references the Car header file, which contains a class to create Car objects - not altering the header file as per assignment instructions
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
    {
        cout << "    ";
        car.print(); // using the .print() nethod in the Car class to print each Car object stored in the deque
    }

    while (!tollBoothLine.empty()) // as long as the deque is not empty (.empty()) - meaning cars are still in line
    {
        cout << endl;
        cout << "Time: " << timePeriod << endl; // output the current time period

        // creating 2 if statements so that probability events can be handled independently from one another
        // this means that during a time period, there is a possibility that both events will occur - a car leaving and a car joining, which is an accurate situation for a toll booth
        // there is also a possibility that no events occur during a time period - no car leaves and no car joins
        // this mimics a situation where a car may not leave because there is a delay when processing payment at the toll booth and a car simply may not join because there are no incoming cars
        
        if (probability <= HEAD_CAR_PAYS_LEAVES) // handle the case where the car at the head of the line pays & leaves
        {
            // I am displaying the car's information first before using .pop_back() so that I can access the car's information directly before removing it from the deque
            // this is valid because the while loop above performs a check to ensure that we will not remove from an empty deque
            cout << "Operation: Car paid: ";
            tollBoothLine.front().print(); // access the information of the head car by using .front() & print its info using .print() from the Car class
            tollBoothLine.pop_front(); // remove the head car from the deque by using .pop_front()
        }

        probability = rand() % 100 + 1; // generate probability for the next case
        if (probability <= CAR_JOINS) // handle the case where another car joins the line
        {
            tollBoothLine.push_back(Car()); // using .push_back() to add a Car object (using the Car class) to the back of the deque (end of the line)
            cout << "Operation: Joined lane: ";
            tollBoothLine.back().print(); // access the information of the new car at the end of the line by using .back() & print its info using .print() from the Car class
        }

        // after each time period, display the queue
        if (tollBoothLine.empty()) // use .empty() to check if the deque has any more cars in line
        {
            // if there are no Car objects in the deque, the queue is empty
            cout << "Queue:" << endl;
            cout << "    Empty" << endl;
        }
        else // display the Car objects in the deque (line)
        {
            cout << "Queue:" << endl;
            for (auto car : tollBoothLine) // using a range-based for loop and the "auto" keyword to output the contents of the std::deque
            {
                cout << "    ";
                car.print(); // using the .print() nethod in the Car class to print each Car object stored in the deque
            }
        }

        timePeriod++; // increment the time period counter for accurate output of time during the next loop
    }
    
    return 0;
}
