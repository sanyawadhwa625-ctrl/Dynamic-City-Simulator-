#include <stdio.h>
#include <string.h>
#include "priority_queue.h"

// Initialize priority queue
void initializePriorityQueue(PriorityQueue *pq)
{
    pq->size = 0;
}

// Insert emergency vehicle
void insertEmergencyVehicle(
    PriorityQueue *pq,
    int vehicleID,
    const char *type,
    int priority
)
{
    if (pq->size == MAX_EMERGENCY)
    {
        printf("\nEmergency queue is FULL!\n");
        return;
    }

    int i = pq->size;

    /*
       Higher priority number means
       higher priority.
    */

    while (i > 0 &&
           pq->vehicles[i - 1].priority < priority)
    {
        pq->vehicles[i] = pq->vehicles[i - 1];
        i--;
    }

    pq->vehicles[i].vehicleID = vehicleID;

    strcpy(
        pq->vehicles[i].type,
        type
    );

    pq->vehicles[i].priority = priority;

    pq->size++;

    printf("\nEmergency vehicle %d (%s) added.",
           vehicleID,
           type);
}

// Remove highest-priority vehicle
void removeEmergencyVehicle(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("\nEmergency queue is EMPTY!\n");
        return;
    }

    printf("\nEmergency vehicle %d (%s) dispatched.",
           pq->vehicles[0].vehicleID,
           pq->vehicles[0].type);

    for (int i = 0; i < pq->size - 1; i++)
    {
        pq->vehicles[i] = pq->vehicles[i + 1];
    }

    pq->size--;
}

// Display priority queue
void displayEmergencyQueue(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("\nEmergency queue is EMPTY!\n");
        return;
    }

    printf("\n");
    printf("============================================\n");
    printf("          EMERGENCY PRIORITY QUEUE\n");
    printf("============================================\n");

    for (int i = 0; i < pq->size; i++)
    {
        printf(
            "Vehicle ID: %d | Type: %s | Priority: %d\n",
            pq->vehicles[i].vehicleID,
            pq->vehicles[i].type,
            pq->vehicles[i].priority
        );
    }
}