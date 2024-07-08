#ifndef GENREINFO_H
#define GENREINFO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "songinfo.h"

// ADD GENREINFO FUNCTIONS
typedef struct GenreInfo {
   char *genreName;     
   int songCount;       // the count of songs in the genre
} GenreInfo;

typedef struct LLNode {
   GenreInfo gi;                   // contains the genre information 
   struct LLNode * next;           // points to the next node in the linked list
} LLNode;

void createLLFromList(LLNode ** uniqueGenreLLPtr, char ** genreList, int genreNameCount);
LLNode * createLinkedListNode(GenreInfo gi);
void generateUniqueGenresLL(LLNode ** headPP, ArrayList_of_Songs songList);
void getUniqueGenres(ArrayList_of_Songs songList, char *** genreListPtr, int * genreListSize);
void createLLFromList(LLNode ** uniqueGenreLLPtr, char ** genreList, int genreNameCount);
void countSongsInEachGenre(LLNode * uniqueGenreLL, ArrayList_of_Songs songList);
void printGenres(LLNode *head);
#endif