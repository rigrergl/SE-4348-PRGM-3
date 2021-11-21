/*************************************************************************** 
 * File: FaultCalculator.h
 * Author: Rigre Garciandia
 * Procedures:  
 * LRU   - runs the test using the LRU replacement algorithm 
 * FIFO  - runs the test using the FIFO replacement algorithm 
 * Clock - runs the test using the Clock replacement algorithm 
***************************************************************************/

#ifndef FAULT_CALCULATOR_H
#define FAULT_CALCULATOR_H

int LRU (int workingSetSize, int trace[1000]);
int FIFO (int workingSetSize, int trace[1000]);
int Clock (int workingSetSize, int trace[1000]);

#endif

