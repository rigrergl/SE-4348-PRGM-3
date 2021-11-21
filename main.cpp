/*************************************************************************** 
 * File: main.cpp
 * Author: Rigre Garciandia
 * Procedures:  
 * main   - test program which runs the Monte Carlo Simulation  
 * normal - returns a random number with normal deviation using mean 10 and SD of 2
 * printColumn - prints a column to console of specified width 
***************************************************************************/

#include <string.h>
#include <iostream>
#include <random>
#include "FaultCalculator.h"
#include <iomanip>

std::default_random_engine generator;
std::normal_distribution<double> distribution(10.0, 2.0);

int LRUResults[21];   //number of page faults using LRU
int FIFOResults[21];  //number of page faults using FIFO
int ClockResults[21]; //number of page faults using Clock

/***************************************************************************  
* int normal()
* Author: Rigre Garciandia 
* Date:  21 November 2021  
* Description: returns a random number with normal deviation using mean 10 and SD of 2
* Parameters: none
**************************************************************************/
int normal()
{
    int number = (int)(distribution(generator));
    return number;
}

/***************************************************************************  
* template <typename T> void printColumn(T t, const int &width)
* Author: Rigre Garciandia 
* Date:  21 November 2021  
* Description: prints a column to console of specified width 
* Parameters:  
*   t       I/P T   The object to print  
*   width   I/P int The specified width   
**************************************************************************/
template <typename T> void printColumn(T t, const int &width)
{
    std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}

/***************************************************************************  
* int main( int argc, char *argv[] ) 
* Author: Rigre Garciandia  
* Date:  21 November 2021 
* Description: test program which runs the Monte Carlo Simulation  
* Parameters:  
*   argc I/P int  The number of arguments on the command line  
*   argv I/P char *[] The arguments on the command line  
*   main O/P int  Status code (not currently used)  
**************************************************************************/
int main(int argc, char *argv[])
{
    for (int i = 0; i < 1000; i++) // Experiments loop
    {
        int data[1000];

        for (int j = 0; j < 1000; j++) //Trace loop
        {
            // Generate a random number from a normal distribution
            // with a mean of ten and a standard deviation of two.
            // There are ten regions which have their own base address.
            data[j] = (10 * ((int)(j / 100))) + normal();
        }

        for (int wss = 4; wss <= 20; wss++)
        {
            // Determine and accumulate the number of page
            // faults for each algorithm base on the current
            // working set size and the current trace.
            LRUResults[wss] += LRU(wss, data);
            FIFOResults[wss] += FIFO(wss, data);
            ClockResults[wss] += Clock(wss, data);
        }
    }

    printColumn("wss", 7);
    printColumn("LRU", 10);
    printColumn("FIFO", 10);
    printColumn("Clock", 10);
    std::cout << std::endl;

    for (int wss = 4; wss <= 20; wss++)
    {
        //output statistics
        double LRUAverageFaults = (double)LRUResults[wss] / 1000;
        double FIFOAverageFaults = (double)FIFOResults[wss] / 1000;
        double ClockAverageFaults = (double)ClockResults[wss] / 1000;

        printColumn(wss, 7);
        printColumn(LRUAverageFaults, 10);
        printColumn(FIFOAverageFaults, 10);
        printColumn(ClockAverageFaults, 10);
        std::cout << std::endl;
    }
}