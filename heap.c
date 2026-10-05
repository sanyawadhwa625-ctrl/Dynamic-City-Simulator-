#include <stdio.h>
#include "heap.h"

// Initialize heap
void initializeHeap(MaxHeap *heap)
{
    heap->size = 0;
}

// Insert road into Max Heap
void insertRoad(
    MaxHeap *heap,
    int roadID,
    int congestion
)
{
    if (heap->size == MAX_ROADS)
    {
        printf("\nRoad congestion heap is FULL!\n");
        return;
    }

    int i = heap->size;

    heap->roads[i].roadID = roadID;
    heap->roads[i].congestion = congestion;

    heap->size++;

    /*
       Move the new road upward
       until Max Heap property is maintained.
    */

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap->roads[parent].congestion >=
            heap->roads[i].congestion)
        {
            break;
        }

        Road temp = heap->roads[parent];

        heap->roads[parent] = heap->roads[i];

        heap->roads[i] = temp;

        i = parent;
    }

    printf("\nRoad %d added with congestion level %d.",
           roadID,
           congestion);
}

// Display the most congested road
void displayMostCongested(MaxHeap *heap)
{
    if (heap->size == 0)
    {
        printf("\nNo road congestion data available.\n");
        return;
    }

    printf("\n");
    printf("============================================\n");
    printf("          ROAD CONGESTION - MAX HEAP\n");
    printf("============================================\n");

    printf("Most congested road: Road %d\n",
           heap->roads[0].roadID);

    printf("Congestion level: %d\n",
           heap->roads[0].congestion);
}