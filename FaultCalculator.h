#ifndef FAULT_CALCULATOR_H
#define FAULT_CALCULATOR_H

int LRU (int workingSetSize, int *trace);
int FIFO (int workingSetSize, int *trace);
int Clock (int workingSetSize, int *trace);

#endif

