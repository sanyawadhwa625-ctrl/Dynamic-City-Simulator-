#include <stdio.h>
#include <string.h>
#include "graph.h"

// Initialize the city graph
void initializeGraph(Graph *graph)
{
    graph->locationCount = 0;

    for (int i = 0; i < MAX_LOCATIONS; i++)
    {
        for (int j = 0; j < MAX_LOCATIONS; j++)
        {
            graph->edges[i][j].destination = -1;
            graph->edges[i][j].distance = 0;
            graph->edges[i][j].traffic = 0;
            graph->edges[i][j].closed = 0;
        }
    }
}

// Add a location to the city
int addLocation(Graph *graph, int id, const char *name)
{
    if (graph->locationCount >= MAX_LOCATIONS)
    {
        printf("Maximum number of locations reached.\n");
        return 0;
    }

    graph->locations[graph->locationCount].id = id;

    strcpy(
        graph->locations[graph->locationCount].name,
        name
    );

    graph->locationCount++;

    return 1;
}

// Add a road between two locations
int addRoad(
    Graph *graph,
    int source,
    int destination,
    int distance
)
{
    if (source < 0 || destination < 0 ||
        source >= MAX_LOCATIONS ||
        destination >= MAX_LOCATIONS)
    {
        return 0;
    }

    graph->edges[source][destination].destination = destination;
    graph->edges[source][destination].distance = distance;

    // Since our city roads are two-way
    graph->edges[destination][source].destination = source;
    graph->edges[destination][source].distance = distance;

    return 1;
}

// Display the complete city road network
void displayGraph(Graph *graph)
{
    printf("\n");
    printf("============================================\n");
    printf("          CITY ROAD NETWORK\n");
    printf("============================================\n");

    for (int i = 0; i < graph->locationCount; i++)
    {
        printf("\n[%d] %s\n",
               graph->locations[i].id,
               graph->locations[i].name);

        for (int j = 0; j < graph->locationCount; j++)
        {
            if (graph->edges[i][j].destination != -1)
            {
                printf("    -> %s | Distance: %d km",
                       graph->locations[j].name,
                       graph->edges[i][j].distance);

                if (graph->edges[i][j].closed)
                {
                    printf(" | ROAD CLOSED");
                }

                printf("\n");
            }
        }
    }
}

// Close a road
void closeRoad(
    Graph *graph,
    int source,
    int destination
)
{
    if (graph->edges[source][destination].destination == -1)
    {
        printf("\nRoad does not exist.\n");
        return;
    }

    graph->edges[source][destination].closed = 1;
    graph->edges[destination][source].closed = 1;

    printf("\nRoad closed successfully.\n");
}

// Open a previously closed road
void openRoad(
    Graph *graph,
    int source,
    int destination
)
{
    if (graph->edges[source][destination].destination == -1)
    {
        printf("\nRoad does not exist.\n");
        return;
    }

    graph->edges[source][destination].closed = 0;
    graph->edges[destination][source].closed = 0;

    printf("\nRoad opened successfully.\n");
}

// Dijkstra's shortest path algorithm
void dijkstra(
    Graph *graph,
    int source,
    int destination
)
{
    int distance[MAX_LOCATIONS];
    int visited[MAX_LOCATIONS];
    int previous[MAX_LOCATIONS];

    // Initialize arrays
    for (int i = 0; i < MAX_LOCATIONS; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        previous[i] = -1;
    }

    distance[source] = 0;

    // Main Dijkstra loop
    for (int count = 0;
         count < graph->locationCount;
         count++)
    {
        int minDistance = INF;
        int current = -1;

        // Find unvisited node with minimum distance
        for (int i = 0;
             i < graph->locationCount;
             i++)
        {
            if (!visited[i] &&
                distance[i] < minDistance)
            {
                minDistance = distance[i];
                current = i;
            }
        }

        if (current == -1)
        {
            break;
        }

        visited[current] = 1;

        // Update neighboring locations
        for (int i = 0;
             i < graph->locationCount;
             i++)
        {
            Edge *edge = &graph->edges[current][i];

            if (edge->destination != -1 &&
                !edge->closed &&
                !visited[i])
            {
                int newDistance =
                    distance[current] + edge->distance;

                if (newDistance < distance[i])
                {
                    distance[i] = newDistance;
                    previous[i] = current;
                }
            }
        }
    }

    // Destination cannot be reached
    if (distance[destination] == INF)
    {
        printf("\nNo route is available between these locations.\n");
        return;
    }

    printf("\n");
    printf("============================================\n");
    printf("             SHORTEST ROUTE\n");
    printf("============================================\n");

    printf("Total distance: %d km\n",
           distance[destination]);

    // Store path
    int path[MAX_LOCATIONS];
    int pathCount = 0;

    int current = destination;

    while (current != -1)
    {
        path[pathCount] = current;
        pathCount++;

        current = previous[current];
    }

    printf("Route: ");

    for (int i = pathCount - 1; i >= 0; i--)
    {
        printf("%s",
               graph->locations[path[i]].name);

        if (i != 0)
        {
            printf(" -> ");
        }
    }

    printf("\n");
}