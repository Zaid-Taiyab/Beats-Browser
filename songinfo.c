#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "songinfo.h"

char * extractString(char * line){
    char *copy=strdup(line);
    char * token = NULL;
    token=strtok(copy, "\t\x09");
    token=strtok(NULL,"\t\x09");

    token[strlen(token) -1]=0;
    token++;
    token++;
    token[strlen(token)-1]=0;
    char *output=strdup(token);
    free(copy);
    return output;
}

static void increaseArrayList_of_SongsCapacity(ArrayList_of_Songs * list);

void createArrayList(ArrayList_of_Songs* listPtr, int initialCapacity){
    // Code : create a single pointer ArrayList 
    // Code : set the  new variable equal to *listPtr;
    ArrayList_of_Songs *al;
    al=listPtr;
    al->songs=malloc(sizeof(Song)*initialCapacity);
    al->count=0;
    al->capacity=initialCapacity;
}

void addElement(ArrayList_of_Songs *list, Song song) {
    // Code : increase capacity if necessary
    increaseArrayList_of_SongsCapacity(list);
    // Code : increase size  
    list->songs[list->count]=song;
    // Increase size
    list->count++;
}

void freeArrayList(ArrayList_of_Songs *list) {    
    free(list->songs);
    free(list);
}

static void increaseArrayList_of_SongsCapacity(ArrayList_of_Songs *list){
    // Code:  if the current size is the same as capacity then we are out of room
        // Code: double the capacity
        // Code: re-allocate the space
        if (list->count==list->capacity) {
            list->capacity *= 2;
            list->songs = realloc(list->songs, sizeof(Song)*(list->capacity));
        }
}

bool addSongFromString(char *line_in, ArrayList_of_Songs *songList) {
    
    return true;
}
//genre	artist_name	track_name	track_id	popularity
// Rap	Post Malone	Too Young	4SYUUlkScpNR1QvPscXf8t	76
bool loadSongs(char * songFile, ArrayList_of_Songs *songList) {
    FILE *file=fopen(songFile, "r");
    if (!file){
        printf("Failed to open file\n");
        return false;
    }
    char *line = NULL;
    size_t read;
    size_t len;
    int count=0;
    while((read=getline(&line, &len, file))!=-1){
        if (line[read -1] == '\n'){
            line[read -1] = 0;
            read--;
        }
        if (strstr(line, "\"genre\"")){
            
        }
        if (count>0){
          char *line2=NULL;
          line2=strdup(line);
          char *genreOfSong=strtok(line2, "\t");
          char *artistOfSong=strtok(NULL, "\t");
          char *titleOfSong=strtok(NULL, "\t");
          char *albumOfSong=strtok(NULL, "\t");
          Song song;
          song.genre=genreOfSong;
          song.artist=artistOfSong;
          song.title=titleOfSong;
          song.album=albumOfSong;
          addElement(songList, song);
        }
        count++;    
    }
    return true;
}
void printSongList(ArrayList_of_Songs songList, int starting_index) {
    if(starting_index<0){
        starting_index=0;
    }
    int index=starting_index;
    for(int i=starting_index;i<starting_index+10;++i){
        Song song = songList.songs[i];
        index+=1;
        printf("%d. %s - %s - %s\n", index, song.genre, songList.songs[i].artist, songList.songs[i].title);
    }
}




