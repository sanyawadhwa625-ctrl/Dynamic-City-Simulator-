#ifndef GRAPH_H
#define GRAPH_H

#define MAX_LOCATIONS 20
#define INF 999999

// Structure for a city location
typedef struct
{
    int id;
    char name[50];
} Location;

// Structure for a road
typedef struct
{
    int destination;
    int distance;
    int traffic;
    int closed;
} Edge;

// Structure for the complete city graph
typedef struct
{
    Location locations[MAX_LOCATIONS];
    Edge edges[MAX_LOCATIONS][MAX_LOCATIONS];
    int locationCount;
} Graph;

// Graph functions
void initializeGraph(Graph *graph);

int addLocation(
    Graph *graph,
    int id,
    const char *name
);

int addRoad(
    Graph *graph,
    int source,
    int destination,
    int distance
);

void displayGraph(Graph *graph);

// Dijkstra shortest path
void dijkstra(
    Graph *graph,
    int source,
    int destination
);

// Dynamic road control
void closeRoad(
    Graph *graph,
    int source,
    int destination
);

void openRoad(
    Graph *graph,
    int source,
    int destination
);

#endif