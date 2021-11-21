#ifndef FAULT_CALCULATOR_H
#define FAULT_CALCULATOR_H

int LRU (int workingSetSize, int trace[1000]);
int FIFO (int workingSetSize, int trace[1000]);
int Clock (int workingSetSize, int trace[1000]);

#endif

