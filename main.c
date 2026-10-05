#include <stdio.h>

#include "graph.h"
#include "queue.h"
#include "priority_queue.h"
#include "heap.h"
#include "hashmap.h"

int main()
{
    // Create all DSA structures
    Graph city;
    Queue trafficQueue;
    PriorityQueue emergencyQueue;
    MaxHeap congestionHeap;
    HashMap cityObjects;

    // Initialize all structures
    initializeGraph(&city);
    initializeQueue(&trafficQueue);
    initializePriorityQueue(&emergencyQueue);
    initializeHeap(&congestionHeap);
    initializeHashMap(&cityObjects);

    // ----------------------------------------
    // CREATE CITY LOCATIONS
    // ----------------------------------------

    addLocation(&city, 0, "City Center");
    addLocation(&city, 1, "School");
    addLocation(&city, 2, "Hospital");
    addLocation(&city, 3, "Residential Area");
    addLocation(&city, 4, "Market");

    // ----------------------------------------
    // CREATE CITY ROADS
    // ----------------------------------------

    addRoad(&city, 0, 1, 4);
    addRoad(&city, 0, 2, 6);
    addRoad(&city, 0, 3, 5);
    addRoad(&city, 1, 4, 3);
    addRoad(&city, 3, 4, 4);

    // ----------------------------------------
    // ADD CITY OBJECTS TO HASH MAP
    // ----------------------------------------

    insertObject(
        &cityObjects,
        101,
        "City Hospital",
        "Hospital"
    );

    insertObject(
        &cityObjects,
        102,
        "Green Valley School",
        "School"
    );

    insertObject(
        &cityObjects,
        103,
        "Central Market",
        "Market"
    );

    insertObject(
        &cityObjects,
        104,
        "City Police Station",
        "Police Station"
    );

    int choice;

    // ----------------------------------------
    // MAIN MENU
    // ----------------------------------------

    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("         DYNAMIC CITY SIMULATOR\n");
        printf("============================================\n");

        printf("1. Display City Road Network\n");
        printf("2. Find Shortest Route\n");
        printf("3. Traffic Management\n");
        printf("4. Emergency Vehicle Management\n");
        printf("5. Road Congestion Monitoring\n");
        printf("6. City Object Search\n");
        printf("7. Simulate Accident\n");
        printf("8. Open Closed Road\n");
        printf("9. Exit\n");

        printf("--------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nDisplaying city road network...\n");
                displayGraph(&city);
                break;

            case 2:
                printf("\nFinding shortest route...\n");

                // Residential Area -> Hospital
                dijkstra(&city, 3, 2);
                break;

            case 3:
                printf("\nTraffic Management\n");

                enqueue(
                    &trafficQueue,
                    101,
                    "Car"
                );

                enqueue(
                    &trafficQueue,
                    102,
                    "Bus"
                );

                enqueue(
                    &trafficQueue,
                    103,
                    "Bike"
                );

                displayQueue(&trafficQueue);

                printf("\nRemoving first vehicle...\n");

                dequeue(&trafficQueue);

                displayQueue(&trafficQueue);
                break;

            case 4:
                printf("\nEmergency Vehicle Management\n");

                insertEmergencyVehicle(
                    &emergencyQueue,
                    201,
                    "Ambulance",
                    10
                );

                insertEmergencyVehicle(
                    &emergencyQueue,
                    202,
                    "FireTruck",
                    8
                );

                insertEmergencyVehicle(
                    &emergencyQueue,
                    203,
                    "PoliceCar",
                    6
                );

                displayEmergencyQueue(
                    &emergencyQueue
                );

                printf("\nDispatching highest-priority vehicle...\n");

                removeEmergencyVehicle(
                    &emergencyQueue
                );

                displayEmergencyQueue(
                    &emergencyQueue
                );

                break;

            case 5:
                printf("\nRoad Congestion Monitoring\n");

                insertRoad(
                    &congestionHeap,
                    101,
                    40
                );

                insertRoad(
                    &congestionHeap,
                    102,
                    85
                );

                insertRoad(
                    &congestionHeap,
                    103,
                    60
                );

                insertRoad(
                    &congestionHeap,
                    104,
                    95
                );

                displayMostCongested(
                    &congestionHeap
                );

                break;

            case 6:
            {
                int id;

                printf("\nEnter City Object ID: ");
                scanf("%d", &id);

                searchObject(
                    &cityObjects,
                    id
                );

                break;
            }

            case 7:
                printf("\nAccident Simulation\n");

                printf("Closing road between Residential Area ");
                printf("and City Center...\n");

                closeRoad(
                    &city,
                    3,
                    0
                );

                printf("\nRoad status updated.\n");

                printf("\nRecalculating route from ");
                printf("Residential Area to Hospital...\n");

                dijkstra(
                    &city,
                    3,
                    2
                );

                break;

            case 8:
                printf("\nOpening road between Residential Area ");
                printf("and City Center...\n");

                openRoad(
                    &city,
                    3,
                    0
                );

                printf("\nRoad is now open.\n");

                break;

            case 9:
                printf("\n============================================\n");
                printf("     Exiting Dynamic City Simulator...\n");
                printf("============================================\n");

                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}