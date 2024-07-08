#ifndef SONGINFO_H
#define SONGINFO_H
#define CHAR_SIZE 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Song {
    char *genre;
    char *artist;
    char *title;
    char *album;
} Song;

typedef struct ArrayList_of_Songs {
    Song *songs;          // pointer to the heap-based array
    size_t count;         // number of elements loaded into the list
    size_t capacity;      // the number of elements that the list can hold before it must be reallocated
} ArrayList_of_Songs;

// Initialize the ArrayList
void createArrayList(ArrayList_of_Songs * listPtr, int initialCapacity);

// Add an item to the ArrayList
void addElement(ArrayList_of_Songs * list, Song song);

// Clean up the ArrayList
void freeArrayList(ArrayList_of_Songs *list);

bool loadSongs(char * songFile, ArrayList_of_Songs *songList);

void printSongList(ArrayList_of_Songs songList, int starting_index);

#endif
