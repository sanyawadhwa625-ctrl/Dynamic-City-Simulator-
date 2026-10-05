#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "queue.h"
#include "priority_queue.h"
#include "heap.h"
#include "hashmap.h"

Graph graph;
Queue trafficQueue;
PriorityQueue emergencyQueue;
MaxHeap congestionHeap;
HashMap cityObjects;


/* -----------------------------------------
   INITIALIZE NOVA CITY
----------------------------------------- */

void initializeCity()
{
    initializeGraph(&graph);
    initializeQueue(&trafficQueue);
    initializePriorityQueue(&emergencyQueue);
    initializeHeap(&congestionHeap);
    initializeHashMap(&cityObjects);


    /* LOCATIONS */

    addLocation(
        &graph,
        0,
        "Residential Area"
    );

    addLocation(
        &graph,
        1,
        "City Center"
    );

    addLocation(
        &graph,
        2,
        "Hospital"
    );

    addLocation(
        &graph,
        3,
        "School"
    );

    addLocation(
        &graph,
        4,
        "Market"
    );

    addLocation(
        &graph,
        5,
        "Police Station"
    );


    /* ROADS */

    addRoad(&graph, 0, 1, 5);

    addRoad(&graph, 0, 3, 4);

    addRoad(&graph, 1, 2, 6);

    addRoad(&graph, 1, 4, 3);

    addRoad(&graph, 2, 5, 2);

    addRoad(&graph, 3, 4, 2);

    addRoad(&graph, 4, 5, 4);


    /* CITY OBJECTS */

    insertObject(
        &cityObjects,
        101,
        "City Hospital",
        "Hospital"
    );

    insertObject(
        &cityObjects,
        102,
        "Central School",
        "School"
    );

    insertObject(
        &cityObjects,
        103,
        "City Market",
        "Market"
    );

    insertObject(
        &cityObjects,
        104,
        "Police Station",
        "Police Station"
    );
}


/* -----------------------------------------
   TRAFFIC QUEUE
----------------------------------------- */

void runTraffic()
{
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

    printf(
        "\nTraffic Queue updated successfully.\n"
    );

    displayQueue(
        &trafficQueue
    );
}


/* -----------------------------------------
   EMERGENCY PRIORITY QUEUE
----------------------------------------- */

void runEmergency()
{
    insertEmergencyVehicle(
        &emergencyQueue,
        201,
        "Ambulance",
        10
    );

    insertEmergencyVehicle(
        &emergencyQueue,
        202,
        "Fire Truck",
        8
    );

    insertEmergencyVehicle(
        &emergencyQueue,
        203,
        "Police Car",
        6
    );

    printf(
        "\nEmergency Priority Queue updated.\n"
    );

    displayEmergencyQueue(
        &emergencyQueue
    );
}


/* -----------------------------------------
   CONGESTION MAX HEAP
----------------------------------------- */

void runCongestion()
{
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
}


/* -----------------------------------------
   ACCIDENT
----------------------------------------- */

void runAccident()
{
    /*
       Road between City Center
       and Hospital is closed.
    */

    closeRoad(
        &graph,
        1,
        2
    );

    printf(
        "\nAccident processed by C Graph.\n"
    );

    printf(
        "Road 1 -> 2 has been closed.\n"
    );
}


/* -----------------------------------------
   OPEN ROAD
----------------------------------------- */

void runOpenRoad()
{
    openRoad(
        &graph,
        1,
        2
    );

    printf(
        "\nRoad reopening processed by C Graph.\n"
    );

    printf(
        "Road 1 -> 2 is open again.\n"
    );
}


/* -----------------------------------------
   SHORTEST ROUTE
----------------------------------------- */

void runRoute()
{
    printf(
        "\nCalculating shortest route...\n"
    );

    dijkstra(
        &graph,
        0,
        2
    );
}


/* -----------------------------------------
   COMMAND PROCESSOR
----------------------------------------- */

int main(int argc, char *argv[])
{
    initializeCity();


    /*
       If no command is supplied,
       show the complete backend demo.
    */

    if (argc < 2)
    {
        printf("\n");
        printf(
            "============================================\n"
        );

        printf(
            "          NOVA CITY C BACKEND\n"
        );

        printf(
            "============================================\n"
        );


        printf("\n1. CITY ROAD NETWORK\n");

        displayGraph(
            &graph
        );


        printf("\n2. SHORTEST ROUTE\n");

        runRoute();


        printf("\n3. TRAFFIC QUEUE\n");

        runTraffic();


        printf("\n4. EMERGENCY VEHICLES\n");

        runEmergency();


        printf("\n5. ROAD CONGESTION\n");

        runCongestion();


        printf("\n6. CITY OBJECT SEARCH\n");

        searchObject(
            &cityObjects,
            101
        );


        printf("\n");
        printf(
            "============================================\n"
        );

        printf(
            "        C BACKEND TEST COMPLETED\n"
        );

        printf(
            "============================================\n"
        );

        return 0;
    }


    /*
       Specific commands
    */

    if (strcmp(argv[1], "traffic") == 0)
    {
        runTraffic();
    }

    else if (
        strcmp(argv[1], "emergency") == 0
    )
    {
        runEmergency();
    }

    else if (
        strcmp(argv[1], "accident") == 0
    )
    {
        runAccident();
    }

    else if (
        strcmp(argv[1], "open") == 0
    )
    {
        runOpenRoad();
    }

    else if (
        strcmp(argv[1], "route") == 0
    )
    {
        runRoute();
    }

    else if (
        strcmp(argv[1], "congestion") == 0
    )
    {
        runCongestion();
    }

    else
    {
        printf(
            "Unknown command: %s\n",
            argv[1]
        );

        return 1;
    }


    return 0;
}