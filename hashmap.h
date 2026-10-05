#ifndef HASHMAP_H
#define HASHMAP_H

#define HASH_SIZE 50

// Structure for a city object
typedef struct
{
    int id;
    char name[50];
    char type[30];
    int occupied;
} CityObject;

// Hash Map structure
typedef struct
{
    CityObject table[HASH_SIZE];
} HashMap;

// Hash Map functions
void initializeHashMap(HashMap *map);

void insertObject(
    HashMap *map,
    int id,
    const char *name,
    const char *type
);

void searchObject(
    HashMap *map,
    int id
);

void displayObjects(
    HashMap *map
);

#endif