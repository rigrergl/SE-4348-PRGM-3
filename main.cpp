#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>

#include <iostream>
#include <random>

std::default_random_engine generator;
std::normal_distribution<double> distribution(10.0, 2.0);

int normal() {
    int number = (int)(distribution(generator));
    return number;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 1000; i++) // Experiments loop
    {
        int data[1000];

        for (int j = 0; j < 1000; j++) //Trace loop
            // Generate a random number from a normal distribution
            // with a mean of ten and a standard deviation of two.
            // There are ten regions which have their own base address.
            data[j] = ( 10 * ((int) ( j / 100 )) ) + normal();

            for (int wss = 4; wss <= 20; wss++)
            {
                // Determine and accumulate the number of page
                // faults for each algorithm base on the current
                // working set size and the current trace.
                // LRUResults  [wss] += LRU  ( wss, data );
                // FIFOResults [wss] += FIFO ( wss, data );
                // ClockResults[wss] += Clock( wss, data );
            }
    }

    for (int wss = 4; wss <= 20; wss++)
    {
        //output statistics
        // Output LRUResults  [wss];
        // Output FIFOResults [wss];
        // Output ClockResults[wss];
    }
}