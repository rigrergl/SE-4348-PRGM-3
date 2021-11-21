#include "FaultCalculator.h"
#include <bits/stdc++.h>

#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;

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

static bool findAndUpdate(int x, int arr[],
                          bool second_chance[], int frames)

{
    int i;

    for (i = 0; i < frames; i++)
    {

        if (arr[i] == x)
        {
            // Mark that the page deserves a second chance
            second_chance[i] = true;

            // Return 'true', that is there was a hit
            // and so there's no need to replace any page
            return true;
        }
    }

    // Return 'false' so that a page for replacement is selected
    // as he reuested page doesn't exist in memory
    return false;
}

// Updates the page in memory and returns the pointer
static int replaceAndUpdate(int x, int arr[],
                            bool second_chance[], int frames, int pointer)
{
    while (true)
    {

        // We found the page to replace
        if (!second_chance[pointer])
        {
            // Replace with new page
            arr[pointer] = x;

            // Return updated pointer
            return (pointer + 1) % frames;
        }

        // Mark it 'false' as it got one chance
        // and will be replaced next time unless accessed again
        second_chance[pointer] = false;

        //Pointer is updated in round robin manner
        pointer = (pointer + 1) % frames;
    }
}

int Clock(int frames, int trace[])
{
    int pointer, i, l = 1000, x, pf;

    //initially we consider frame 0 is to be replaced
    pointer = 0;

    //number of page faults
    pf = 0;

    // Create a array to hold page numbers
    int arr[frames];

    // No pages initially in frame,
    // which is indicated by -1
    memset(arr, -1, sizeof(arr));

    // Create second chance array.
    // Can also be a byte array for optimizing memory
    bool second_chance[frames];

    for (i = 0; i < l; i++)
    {
        x = trace[i];

        // Finds if there exists a need to replace
        // any page at all
        if (!findAndUpdate(x, arr, second_chance, frames))
        {
            // Selects and updates a victim page
            pointer = replaceAndUpdate(x, arr,
                                       second_chance, frames, pointer);

            // Update page faults
            pf++;
        }
    }

    return pf;
}