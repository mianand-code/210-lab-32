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
const int TOLL_BOOTH_LANE_NUM = 4; // represents the # of toll booth lanes in the plaza
const int INITIAL_LINE_MAX = 3; // represents the maximum # of cars that can join the initial line, will be used to generate a random # of cars between 1-3
const int HEAD_CAR_PAYS_LEAVES = 46; // represents the probability that the car at the head of the line pays its toll and leaves the toll booth
const int CAR_JOINS = 39; // represents the probability that another car will join the line for the toll booth
const int REAR_CAR_SWITCHES = 15; // represents the probability that the rear car will switch lanes
const int CAR_JOINS_EMPTY_LANE = 50; // represents the probability that a new car will join the lane if it is completely empty and there is still more time in the simulation
const int TIME_PERIODS = 20; // represents the # of time periods the simulation will run for

int main()
{
    srand(time(0)); // needed as the first line in main() in order to generate a random # for probability

    // create an array of type deque<Car>
    // will be used to represent the multiple toll booth lanes (4) that each hold their own Car objects
    deque<Car> tollBoothLanes[TOLL_BOOTH_LANE_NUM];

    int probability = rand() % 100 + 1; // generates a random # between 1-100 for probability

    // when the simulation starts, 1-3 cars should already be in line to pay the toll
    for (int l = 0; l < TOLL_BOOTH_LANE_NUM; l++) // for each one of the lanes
    {
        int initialCars = rand() % INITIAL_LINE_MAX + 1; // generate a random # of cars between 1-3 and store it in a variable

        for (int c = 0; c < initialCars; c++) // according to the random # of cars generated
        {
            // use .push_back() to add a Car object (using the Car class) to the back of the deque (lane)
            // [l] accesses a specific lane (array index)
            tollBoothLanes[l].push_back(Car());
        }
    }

    cout << "Initial queue:" << endl; // output the initial/starting queue of cars for each lane
    for (int i = 0; i < TOLL_BOOTH_LANE_NUM; i++) // for each one of the lanes
    {
        cout << "Lane: " << i + 1 << ": " << endl; // output the lane #
        
        // use a range-based for loop and the "auto" keyword to output the Car objects in each of the 4 lanes
        // loop through the array of type deque<Car>
        for (auto car : tollBoothLanes[i]) // [i] accesses a specific lane (array index)
        {
            cout << "    ";
            car.print(); // using the .print() nethod in the Car class to print each Car object stored in the deque
        }
    }

    for (int timePeriod = 1; timePeriod <= TIME_PERIODS; timePeriod++) // simulation will run for 20 time periods & then terminate
    {
        cout << endl;
        cout << "Time: " << timePeriod << endl; // output the current time period

        for (int i = 0; i < TOLL_BOOTH_LANE_NUM; i++) // creation of another for loop to handle each of the lanes
        {
            // creating 3 if statements so that probability events can be handled independently from one another
            // this means that during a time period, there is a possibility that all events can occur - a head car leaving, a car joining, and a rear car switching lanes, which is an accurate situation for a toll booth
            // if a car joins the end of the line and that same car switches lanes in the same time period, this can mimic a situation where the car realizes that it may be better off in a different line that is being processed faster
            // there is also a possibility that no events occur during a time period - no car leaves, no car joins, and no car switches
            // this mimics a situation where a car may not leave because there is a delay when processing payment at the toll booth and a car simply may not join because there are no incoming cars. Also, no car may want/need to switch
            
            // handle the case where the car at the head of the line pays & leaves
            // use .empty() to ensure the lane is not empty before proceeding with head car removal
            if (!tollBoothLanes[i].empty() && probability <= HEAD_CAR_PAYS_LEAVES)
            {
                // I am displaying the car's information first before using .pop_back() so that I can access the car's information directly before removing it from the deque
                // this is valid because the for statement above performs a check to ensure that we will not remove from an empty deque
                cout << "Lane: " << i + 1 << " Paid: ";
                // [i] is used to access a specific lane within the array
                tollBoothLanes[i].front().print(); // access the information of the head car by using .front() & print its info using .print() from the Car class
                tollBoothLanes[i].pop_front(); // remove the head car from the deque by using .pop_front()
            }

            // handle the case where another car joins the line
            // will also handle the situation in which the line is empty, but there is still more time in the simulation
            // there will be a 50/50 probability of a new car joining the line if the line is completely empty
            if (tollBoothLanes[i].empty()) // check if the lane is empty
            {
                probability = rand() % 100 + 1; // generate probability for the case
                if (probability <= CAR_JOINS_EMPTY_LANE) // handle the 50/50 probability case
                {
                    tollBoothLanes[i].push_back(Car()); // using .push_back() to add a Car object (using the Car class) to the back of the deque (end of the line) for a specific lane
                    cout << "Lane: " << i + 1 << " Joined: ";
                    tollBoothLanes[i].back().print(); // access the information of the new car at the end of the line by using .back() & print its info using .print() from the Car class
                }
            }
            else // creation of a matching "else" statement to handle the case where the lane is not empty, which means 50/50 probability does not apply here (39% probability applies here)
            {
                probability = rand() % 100 + 1; // generate probability for this case
                if (probability <= CAR_JOINS)
                {
                    tollBoothLanes[i].push_back(Car()); // using .push_back() to add a Car object (using the Car class) to the back of the deque (end of the line) for a specific lane
                    cout << "Lane: " << i + 1 << " Joined: ";
                    tollBoothLanes[i].back().print(); // access the information of the new car at the end of the line by using .back() & print its info using .print() from the Car class
                }
            }

            // handle the case where a rear car will shift lanes to a random lanes that is not their own
            probability = rand() % 100 + 1; // generate probability for this case
            // use .empty() to ensure the lane is not empty before proceeding with the switching case
            if (!tollBoothLanes[i].empty() && probability <= REAR_CAR_SWITCHES)
            {
                int randomLane; // creation of a variable to hold the random lane # that the car will switch into
                // create a do-while loop so that a random lane # will be generated until a lane number is generated that does not match the one the car is currently in
                do
                {
                    randomLane = rand() % TOLL_BOOTH_LANE_NUM;

                } while (randomLane == i);

                Car switchLaneCar = tollBoothLanes[i].back(); // create a new Car object (switchLaneCar) that will hold/save the data of the rear car in the current lane (this is the car that wants to switch)
                tollBoothLanes[i].pop_back(); // remove the rear car in the current lane by using .pop_back()
                // use .push_back() to move/add the rear car that was in the current lane (switchLaneCar) to the end of the randomly chosen lane
                // [randomLane] accesses the random lane index that was chosen above
                tollBoothLanes[randomLane].push_back(switchLaneCar);
                cout << "Lane: " << i + 1 << " Switched: ";
                switchLaneCar.print(); // display the information of the Car object that switched by using .print() from the Car class
            }
        }

        // after each time period of operations, display the queue for each lane
        for (int i = 0; i < TOLL_BOOTH_LANE_NUM; i++) // for each of the lanes
        {
            if (tollBoothLanes[i].empty()) // use .empty() to check if the deque has any more cars in line
            {
                // if there are no Car objects in the deque, the queue is empty
                cout << "Queue:" << endl;
                cout << "    Empty" << endl;
            }
            else // display the Car objects in the deque (line)
            {
                cout << ''
                for (auto car : tollBoothLine) // using a range-based for loop and the "auto" keyword to output the contents of the std::deque
                {
                    cout << "    ";
                    car.print(); // using the .print() nethod in the Car class to print each Car object stored in the deque
                }
            }
        }
    }
    
    return 0;
}
