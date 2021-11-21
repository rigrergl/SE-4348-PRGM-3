#include <string.h>
#include <iostream>
#include <random>
#include "FaultCalculator.h"

std::default_random_engine generator;
std::normal_distribution<double> distribution(10.0, 2.0);

int LRUResults[21];   //number of page faults using LRU
int FIFOResults[21];  //number of page faults using FIFO
int ClockResults[21]; //number of page faults using Clock

int normal()
{
    int number = (int)(distribution(generator));
    return number;
}

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
            LRUResults  [wss] += LRU  ( wss, data );
            FIFOResults [wss] += FIFO ( wss, data );
            ClockResults[wss] += Clock( wss, data );
        }
    }

    for (int wss = 4; wss <= 20; wss++)
    {
        //output statistics
        double LRUAverageFaults = (double)LRUResults[wss] / 1000;
        double FIFOAverageFaults = (double)FIFOResults[wss] / 1000;
        double ClockAverageFaults = (double)ClockResults[wss] / 1000;

        printf("wss=%d \t LRU:%f \t\t FIFO:%f \t\t Clock:%f \n", 
        wss, 
        LRUAverageFaults, 
        FIFOAverageFaults, 
        ClockAverageFaults);
    }
}