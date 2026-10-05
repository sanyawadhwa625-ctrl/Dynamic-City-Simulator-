#include <stdio.h>
#include <string.h>
#include "queue.h"

// Initialize the queue
void initializeQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

// Check whether queue is empty
int isQueueEmpty(Queue *q)
{
    return q->front == -1;
}

// Check whether queue is full
int isQueueFull(Queue *q)
{
    return q->rear == QUEUE_SIZE - 1;
}

// Add vehicle to queue
void enqueue(
    Queue *q,
    int id,
    const char *type
)
{
    if (isQueueFull(q))
    {
        printf("\nTraffic queue is FULL!\n");
        return;
    }

    // First vehicle
    if (q->front == -1)
    {
        q->front = 0;
    }

    q->rear++;

    q->vehicles[q->rear].vehicleID = id;

    strcpy(
        q->vehicles[q->rear].vehicleType,
        type
    );

    printf("\nVehicle %d (%s) added to traffic queue.\n",
           id,
           type);
}

// Remove vehicle from queue
void dequeue(Queue *q)
{
    if (isQueueEmpty(q))
    {
        printf("\nTraffic queue is EMPTY!\n");
        return;
    }

    printf("\nVehicle %d (%s) passed the traffic signal.\n",
           q->vehicles[q->front].vehicleID,
           q->vehicles[q->front].vehicleType);

    q->front++;

    // Queue becomes empty
    if (q->front > q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
}

// Display all vehicles
void displayQueue(Queue *q)
{
    if (isQueueEmpty(q))
    {
        printf("\nTraffic queue is EMPTY!\n");
        return;
    }

    printf("\n");
    printf("============================================\n");
    printf("             TRAFFIC QUEUE\n");
    printf("============================================\n");

    for (int i = q->front; i <= q->rear; i++)
    {
        printf("Vehicle ID: %d | Type: %s\n",
               q->vehicles[i].vehicleID,
               q->vehicles[i].vehicleType);
    }
}