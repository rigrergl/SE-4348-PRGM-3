#include "FaultCalculator.h"
#include <bits/stdc++.h>

int LRU(int workingSetSize, int trace[1000])
{
    int pageFaults = 0;
    std::unordered_set<int> currentPages;
    std::unordered_map<int, int> pageTimestamps;

    for (int i = 0; i < 1000; i++) //trace loop
    {
        if (currentPages.size() < workingSetSize) //we have free spots
        {
            if (currentPages.find(trace[i]) == currentPages.end())
            {
                currentPages.insert(trace[i]);
            }
            pageTimestamps[trace[i]] = i;
        }
        else
        {
            if (currentPages.find(trace[i]) == currentPages.end())
            {
                pageFaults++;

                //remove the LRU page
                int earliestTimestamp = INT_MAX, pageToRemove;
                for (auto pagesIterator = currentPages.begin(); pagesIterator != currentPages.end(); pagesIterator++)
                {
                    if (pageTimestamps[*pagesIterator] < earliestTimestamp)
                    {
                        earliestTimestamp = pageTimestamps[*pagesIterator];
                        pageToRemove = *pagesIterator;
                    }
                }

                currentPages.erase(pageToRemove);
                currentPages.insert(trace[i]);
            }
            pageTimestamps[trace[i]] = i;
        }
    }

    return pageFaults;
}

int FIFO(int workingSetSize, int trace[1000])
{
    int pageFaults = 0;
    std::unordered_set<int> currentPages;
    std::queue<int> pagesToRemove;

    for (int i = 0; i < 1000; i++) //trace loop
    {
        if (currentPages.size() < workingSetSize &&
            currentPages.find(trace[i]) == currentPages.end()) //we have free spots and the current page does not exist in main memory yet
        {
            currentPages.insert(trace[i]);
            pagesToRemove.push(trace[i]);
        }
        else if (currentPages.find(trace[i]) == currentPages.end()) //must remove a page
        {
            pageFaults++;

            currentPages.erase((int)pagesToRemove.front());
            pagesToRemove.pop();

            currentPages.insert(trace[i]);
            pagesToRemove.push(trace[i]);
        }
    }

    return pageFaults;
}

int Clock(int workingSetSize, int trace[1000])
{
    return 0;
}