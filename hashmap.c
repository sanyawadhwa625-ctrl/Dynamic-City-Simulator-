#include <stdio.h>
#include <string.h>
#include "hashmap.h"

// Hash function
int hashFunction(int id)
{
    return id % HASH_SIZE;
}

// Initialize hash map
void initializeHashMap(HashMap *map)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        map->table[i].occupied = 0;
    }
}

// Insert a city object
void insertObject(
    HashMap *map,
    int id,
    const char *name,
    const char *type
)
{
    int index = hashFunction(id);

    // Linear probing for collision handling
    while (map->table[index].occupied)
    {
        index = (index + 1) % HASH_SIZE;
    }

    map->table[index].id = id;

    strcpy(
        map->table[index].name,
        name
    );

    strcpy(
        map->table[index].type,
        type
    );

    map->table[index].occupied = 1;

    printf("\nCity object %d inserted successfully.",
           id);
}

// Search for a city object
void searchObject(
    HashMap *map,
    int id
)
{
    int index = hashFunction(id);

    int start = index;

    while (map->table[index].occupied)
    {
        if (map->table[index].id == id)
        {
            printf("\n");
            printf("============================================\n");
            printf("             OBJECT FOUND\n");
            printf("============================================\n");

            printf("ID   : %d\n",
                   map->table[index].id);

            printf("Name : %s\n",
                   map->table[index].name);

            printf("Type : %s\n",
                   map->table[index].type);

            return;
        }

        index = (index + 1) % HASH_SIZE;

        if (index == start)
        {
            break;
        }
    }

    printf("\nCity object with ID %d not found.\n",
           id);
}

// Display all objects
void displayObjects(
    HashMap *map
)
{
    printf("\n");
    printf("============================================\n");
    printf("              CITY OBJECTS\n");
    printf("============================================\n");

    int found = 0;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        if (map->table[i].occupied)
        {
            printf(
                "ID: %d | Name: %s | Type: %s\n",
                map->table[i].id,
                map->table[i].name,
                map->table[i].type
            );

            found = 1;
        }
    }

    if (!found)
    {
        printf("No city objects available.\n");
    }
}