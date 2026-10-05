#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 50

// Structure for a vehicle
typedef struct
{
    int vehicleID;
    char vehicleType[30];
} Vehicle;

// Structure for Queue
typedef struct
{
    Vehicle vehicles[QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Queue functions
void initializeQueue(Queue *q);

int isQueueEmpty(Queue *q);

int isQueueFull(Queue *q);

void enqueue(
    Queue *q,
    int id,
    const char *type
);

void dequeue(Queue *q);

void displayQueue(Queue *q);

#endif