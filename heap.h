#ifndef HEAP_H
#define HEAP_H

#define MAX_ROADS 50

// Structure for a road's congestion information
typedef struct
{
    int roadID;
    int congestion;
} Road;

// Max Heap structure
typedef struct
{
    Road roads[MAX_ROADS];
    int size;
} MaxHeap;

// Heap functions
void initializeHeap(MaxHeap *heap);

void insertRoad(
    MaxHeap *heap,
    int roadID,
    int congestion
);

void displayMostCongested(MaxHeap *heap);

#endif