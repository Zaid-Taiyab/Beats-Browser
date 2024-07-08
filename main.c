#include "genreinfo.h"
#include "songinfo.h"
#include<stdio.h>

void menu(char * filename, ArrayList_of_Songs songList, LLNode *head);
void processFileByGenre(char *filename, int choice, int * startingIndex);
void handleGenreSelection(char* choice, int* filtering, int* prevChoice, int* startingIndex, char* filename);
void handleNavigation(char* choice, int* startingIndex, int* filtering, int * startingIndexFilter, int* prevChoice, ArrayList_of_Songs songList, char* filename);

int main(int argc, char *argv[]){
    // Phase 1
    ArrayList_of_Songs songList;
    int initalCapacity1 = 10;
    songList.songs = NULL;
    createArrayList(&songList, initalCapacity1);
    if (argv[1]!=NULL)
    {
        loadSongs(argv[1], &songList);
    }
    else {
        loadSongs("songs2.5k.csv", &songList);
    }

    // Phase 2
    char ** genreList;
    int genreNameCount = 0;
    LLNode *head;
    getUniqueGenres(songList, &genreList, &genreNameCount);
    createLLFromList(&head, genreList, genreNameCount);
    countSongsInEachGenre(head, songList);
    printGenres(head);
    
    printf("\n");
    
    // Phase 3
    if (argv[1]!=NULL)
    {
        menu(argv[1], songList, head);
    }
    else {
        menu("songs2.5k.csv", songList, head);
    }
    free(head);
}

void handleNavigation(char* choice, int* startingIndex, int* filtering, int* startingIndexFilter, int* prevChoice, ArrayList_of_Songs songList, char* filename) {
    if (strcmp(choice, "q") == 0) {
        return;
    } else if (strcmp(choice, "n") == 0) {
        if (*startingIndex < songList.count - 10) {
            *startingIndex += 10;
        }
    } else if (strcmp(choice, "p") == 0) {
        *startingIndex -= 10;
    } else if (strcmp(choice, "s") == 0) {
        *startingIndex = 0;
    } else if (strcmp(choice, "e") == 0) {
        *startingIndex = songList.count - 10;
    } else if (strcmp(choice, "r") == 0) {
        *startingIndex = 0;
        *filtering = 0;
    }
    
    if(*filtering!=0){
        if (strcmp(choice, "q") == 0) {
        return;
        } else if (strcmp(choice, "n") == 0) {
        if (*startingIndexFilter < songList.count - 10) {
            *startingIndexFilter += 10;
        }
        } else if (strcmp(choice, "p") == 0) {
        *startingIndexFilter -= 10;
        } else if (strcmp(choice, "s") == 0) {
        *startingIndexFilter = 0;
        } else if (strcmp(choice, "e") == 0) {
        *startingIndexFilter = songList.count - 10;
        } else if (strcmp(choice, "r") == 0) {
        *startingIndexFilter = 0;
        *filtering = 0;
    }
    }

    if (*filtering == 0) {
        printSongList(songList, *startingIndex);
    } else {
        processFileByGenre(filename, *prevChoice, startingIndexFilter);
    }
}

void handleGenreSelection(char* choice, int* filtering, int* prevChoice, int* startingIndex, char* filename) {
    int genreChoice = 0;
    if (strcmp(choice, "1") == 0) {
        genreChoice = 1;
    } else if (strcmp(choice, "2") == 0) {
        genreChoice = 2;
    } else if (strcmp(choice, "3") == 0) {
        genreChoice = 3;
    } else if (strcmp(choice, "4") == 0) {
        genreChoice = 4;
    } else if (strcmp(choice, "5") == 0) {
        genreChoice = 5;
    } else if (strcmp(choice, "6") == 0) {
        genreChoice = 6;
    } else if (strcmp(choice, "7") == 0) {
        genreChoice = 7;
    }

    if (genreChoice > 0) {
        *filtering = 1;
        *prevChoice = genreChoice;
        processFileByGenre(filename, genreChoice, startingIndex);
    }
}

void menu(char * filename,ArrayList_of_Songs songList, LLNode *head){
    int startingIndex=0;
    int startingIndexFilter=0;
    int arbitraryCounter=0;
    int prevChoice=0;
    int filtering=0;
        while(true){
        char choice[5];
        if (arbitraryCounter<1){
            printSongList(songList,startingIndex);
        }
        arbitraryCounter++;
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("Navigation:     n for next, p for previous, and q to quit, s for start, e for end, r for reset filter.\n");
        printf("[1] Rap - [2] Dance - [3] Pop - [4] Rock - [5] Hip-Hop - [6] Electronic - [7] Ska  ");
        printf("\n");
        scanf("%s", choice);
        if (strcmp(choice, "q") == 0) {
            break;
        } else if (choice[0] >= '1' && choice[0] <= '7') {
            handleGenreSelection(choice, &filtering, &prevChoice, &startingIndexFilter, filename);
        } else {
            handleNavigation(choice, &startingIndex, &filtering, &startingIndexFilter, &prevChoice, songList, filename);
        }
    }
}

void processFileByGenre(char *filename, int choice, int * startingIndexFilter) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.");
        return;
    }
    
    char line[1000];
    const char *wordToCheck = NULL;
    switch (choice) {
        case 4:
            wordToCheck = "Rap";
            break;
        case 7:
            wordToCheck = "Dance";
            break;
        case 5:
            wordToCheck = "Pop";
            break;
        case 6:
            wordToCheck = "Rock";
            break;
        case 3:
            wordToCheck = "Hip-Hop";
            break;
        case 2:
            wordToCheck = "Electronic";
            break;
        case 1:
            wordToCheck = "Ska";
            break;
        default:
            printf("Invalid choice");
            fclose(file);
            return;
    }
    // separate each song into genres and then do it.
    // basically get the genre like you are doing, put the songs of that gnere in an array, then print by 10 each
    struct Song genreSongs[2500];
    int lineSkipper=0;
    int i=0;
    int currentLine[1000];
    int currLine=0;
    while (fgets(line, sizeof(line), file) != NULL) {
            if(lineSkipper>0){
            char *copy = strdup(line);
            char *token = strtok(copy, "\t\x09");
            
            if (token != NULL) {
                char *genre = strdup(token);
                
                if (strcmp(genre, wordToCheck) == 0) {
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
                    genreSongs[i]=song;
                    currentLine[i]=currLine;
                    ++i;
                }
                }
            }
            lineSkipper++;
            currLine++;
        }
        if(*startingIndexFilter>=i){
        for (int j=i-10;j<*startingIndexFilter+10&&j<i;++j){
            if (genreSongs[j].genre!=NULL){
            printf("%d. %s - %s - %s\n", currentLine[j], genreSongs[j].genre, genreSongs[j].artist, genreSongs[j].title);
            }
        }
        }
        for (int j=*startingIndexFilter;j<*startingIndexFilter+10&&j<i;++j){
            if (genreSongs[j].genre!=NULL){
            printf("%d. %s - %s - %s\n", currentLine[j], genreSongs[j].genre, genreSongs[j].artist, genreSongs[j].title);
            }
        }
        //*startingIndex=i;
        fclose(file);
}
// print it again if the songs end

// filtering on, iterate with a different starting index
// filtering off, iterate with a different index





