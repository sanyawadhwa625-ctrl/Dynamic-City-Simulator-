#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MAX_EMERGENCY 50

// Structure for an emergency vehicle
typedef struct
{
    int vehicleID;
    char type[30];
    int priority;
} EmergencyVehicle;

// Structure for Priority Queue
typedef struct
{
    EmergencyVehicle vehicles[MAX_EMERGENCY];
    int size;
} PriorityQueue;

// Priority Queue functions
void initializePriorityQueue(PriorityQueue *pq);

void insertEmergencyVehicle(
    PriorityQueue *pq,
    int vehicleID,
    const char *type,
    int priority
);

void removeEmergencyVehicle(PriorityQueue *pq);

void displayEmergencyQueue(PriorityQueue *pq);

#endif