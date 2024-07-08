#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "songinfo.h"
#include "genreinfo.h"

/**
 * COPY Test cases from Phase 1
*/
void printPassed(const char *format, ...) {
    va_list args;

    // Start red text
    printf("\x1b[32mTest PASSED ");

    // Initialize args to store all arguments after format
    va_start(args, format);

    // Print the formatted string with the variable arguments
    vprintf(format, args);

    // End red text
    printf("\x1b[0m");

    // Cleanup args
    va_end(args);
}

void printFailed(const char *format, ...) {
    va_list args;

    // Start red text
    printf("\x1b[31mTest Failed ");

    // Initialize args to store all arguments after format
    va_start(args, format);

    // Print the formatted string with the variable arguments
    vprintf(format, args);

    // End red text
    printf("\x1b[0m");

    // Cleanup args
    va_end(args);
}


/**
 * This unit test will test whether createArrayList initalizes the list
 */
bool testCreateArrayList(){
    char functionName[] = "createArrayList";
    ArrayList_of_Songs list;
    // char testarr[] = "testarr";
    int initalCapacity1 = 10;
    Song song;
    list.songs = NULL;
    list.songs=&song;

    
    // CODE: ADD CREATE LIST
    createArrayList(&list, initalCapacity1);
    if (list.songs == NULL){
        printFailed("for %s because list.songs is null\n", functionName);
        return false;
    }
    printPassed("for %s\n", functionName);
    return true;

}

bool testAddElement(){
    char functionName[] = "addElement";
    ArrayList_of_Songs list;
    int initalCapacity1 = 10;
    createArrayList(&list, initalCapacity1);
    
    // CODE which ever array location you will test, create a dummy value to make sure that the add element overwrote it
    list.songs->artist="l";
    Song song1 = {"Rap", "Post Malone", "Too Young"};
    addElement(&list, song1);

    if (strcmp(list.songs[0].artist,song1.artist)){
        printFailed("for %s because list.songs[%d].artist == %s instead of '%s'\n", functionName, 0, list.songs[0].artist, song1.artist);
        return false;
    }

    printPassed("for %s\n", functionName);
    return true;

}

bool testLoadSongs_TestFirstValue(){
    char functionName[] = "loadSongs";
    char filename[] = "songsminor.csv";
    ArrayList_of_Songs list;
    
    int initalCapacity1 = 10;
    list.songs = NULL;
    
    createArrayList(&list, initalCapacity1);

    loadSongs(filename, &list);


    if (strcmp(list.songs[0].genre,"Rap") != 0){
        printFailed("for %s because list.songs[%d].genre == %s instead of '%s'\n", functionName, 0, list.songs[0].genre, "Rap");
        return false;
    }
    if (strcmp(list.songs[0].artist,"Post Malone") != 0){
        printFailed("for %s because list.songs[%d].artist == %s instead of '%s'\n", functionName, 0, list.songs[0].artist, "Post Malone");
        return false;
    }
    if (strcmp(list.songs[0].title,"Too Young") != 0){
        printFailed("for %s because list.songs[%d].title == %s instead of '%s'\n", functionName, 0, list.songs[0].title, "Too Young");
        return false;
    }
    printPassed("for %s\n", functionName);
    return true;
}

bool testLoadSongs_TestLastValue(){
    char functionName[] = "loadSongs";
    char filename[] = "songsminor.csv";
    ArrayList_of_Songs list;
    
    int initalCapacity1 = 10;
    list.songs = NULL;
    createArrayList(&list, initalCapacity1);

    loadSongs(filename, &list);
   
    if (strcmp(list.songs[list.count-1].genre,"Rock") != 0){
        printFailed("for %s because list.songs[%d].genre == %s instead of '%s'\n", functionName, 0, list.songs[list.count-1].genre, "Rock");
        return false;
    }
    if (strcmp(list.songs[list.count-1].artist,"Red Hot Chili Peppers") != 0){
        printFailed("for %s because list.songs[%d].artist == %s instead of '%s'\n", functionName, 0, list.songs[list.count-1].artist, "Red Hot Chili Peppers");
        return false;
    }
    if (strcmp(list.songs[list.count-1].title,"Can't Stop") != 0){
        printFailed("for %s because list.songs[%d].title == %s instead of '%s'\n", functionName, 0, list.songs[list.count-1].title, "Can't Stop");
        return false;
    }
    printf("%ld\n", list.count-1);
    printPassed("for %s\n", functionName);
    return true;
}



/**
 * NEW TEST CASES
*/

// getUniqueGenres(ArrayList_of_Songs songList, char *** genreList, int * genreNameCount){
bool testGetUniqueGenres(){
    char functionName[] = "getUniqueGenres";
    char filename[] = "songsminor.csv";
    ArrayList_of_Songs songList;
    
    int initalCapacity1 = 10;
    songList.songs = NULL;
    createArrayList(&songList, initalCapacity1);
    loadSongs(filename, &songList);

    char ** genreList;
    int genreNameCount = 0;

    getUniqueGenres(songList, &genreList, &genreNameCount);
    char *expectedGenres[] = {"Rap","Dance","Pop","Rock","Hip-Hop","Electronic","Ska"};
    int sizeOfExpectedGenres = 7;

    if (genreNameCount != sizeOfExpectedGenres){
        printFailed("for %s because genreListSize is wrong, it is %d which is not equal to sizeOfExpectedGenres %d\n", functionName, genreNameCount, sizeOfExpectedGenres);
        return false; 
    }
    for (int x=0; x < genreNameCount; x++){        
            if (strcmp(genreList[x], expectedGenres[x]) != 0){
                printFailed("for %s because genreList[%d] == %s instead of '%s'\n", functionName, x, genreList[x], expectedGenres[x]);
                return false; 
            }     
    }
    printPassed("for %s\n", functionName);
    return true;
}

//void createLLFromList(LLNode ** uniqueGenreLLPtr, char ** genreList, int genreNameCount)
bool testCreateLLFromList(){
    char functionName[] = "createLLFromList";
    char filename[] = "songsminor.csv";
    ArrayList_of_Songs songList;
    
    int initalCapacity1 = 10;
    songList.songs = NULL;
    createArrayList(&songList, initalCapacity1);
    loadSongs(filename, &songList);

    char ** genreList;
    int genreNameCount = 0;

    getUniqueGenres(songList, &genreList, &genreNameCount);
    LLNode *head;
    createLLFromList(&head, genreList, genreNameCount);
    LLNode *current = head;
    int glIndex = 0;
    while(current != NULL){
        if (strcmp(current->gi.genreName, genreList[glIndex]) != 0){
            printFailed("for %s because for genre name in the Linked List '%s' does not match the genre array genreList[%d]=%s\n", functionName, current->gi.genreName, glIndex, genreList[glIndex]);
            return false; 
        }
        current = current->next;
        glIndex++;
    }
    
    printPassed("for %s\n", functionName);
    return true;
}

// countSongsInEachGenre(LLNode * head, ArrayList_of_Songs songList)
bool testCountSongsInEachGenre(){
    char functionName[] = "countSongsInEachGenre";
    char filename[] = "songsminor.csv";
    ArrayList_of_Songs songList;
    
    int initalCapacity1 = 10;
    songList.songs = NULL;
    createArrayList(&songList, initalCapacity1);
    loadSongs(filename, &songList);

    char ** genreList;
    int genreNameCount = 0;

    getUniqueGenres(songList, &genreList, &genreNameCount);
    LLNode *head;
    createLLFromList(&head, genreList, genreNameCount);
    LLNode *current = head;

    countSongsInEachGenre(head, songList);
    int expectedSongCount[] = {57,42,108,34,52,3,4};
    int i =0;
    while(current != NULL){
        printf("%-10s %d\n", current->gi.genreName, current->gi.songCount);

        if (current->gi.songCount != expectedSongCount[i]){
            printFailed("for %s because for genre name in the Linked List '%s' the count is %d but the expected count is %d\n", functionName, current->gi.songCount, expectedSongCount[i]);
            return false; 
        }
        i++;
        current = current->next;
    }
    
    printPassed("for %s\n", functionName);
    return true;
}

int main(int argc, char **argv){

    // The assert MACRO comes from assert.h and tests for true conditions 
    // if the condition is false, it will stop executing the program and return and error
    if (argc == 1){
        if (!testCreateLLFromList()){
            return 141;
        }
        if (!testGetUniqueGenres()){
            return 140;
        }
        if (!testCountSongsInEachGenre()){
            return 142;
        }
        if (!testCreateArrayList()){
            return 130;
        }
        if (!testAddElement()){
            return 131;
        }
        if (!testLoadSongs_TestFirstValue()){
            return 132;
        }
        if (!testLoadSongs_TestLastValue()){
            return 133;
        }
        printf("All tests completed successfully!\n");
        return 0;
    }
    
    if (strcmp(argv[1], "testCreateArrayList") == 0 || strcmp(argv[1], "1") == 0){
        return testCreateArrayList() ? 0 : 129;
    }
    if (strcmp(argv[1], "testAddElement") == 0 || strcmp(argv[1], "2") == 0){
        return testAddElement() ? 0 : 129;
    }
    if (strcmp(argv[1], "testLoadSongs_TestFirstValue") == 0 || strcmp(argv[1], "3") == 0){
        return testLoadSongs_TestFirstValue() ? 0 : 129;
    }
    if (strcmp(argv[1], "testLoadSongs_TestLastValue") == 0 || strcmp(argv[1], "4") == 0){
        return testLoadSongs_TestLastValue() ? 0 : 129;
    }

    if (strcmp(argv[1], "testCountSongsInEachGenre") == 0 || strcmp(argv[1], "5") == 0){
        return testCreateArrayList() ? 0 : 129;
    }
    if (strcmp(argv[1], "testCreateLLFromList") == 0 || strcmp(argv[1], "6") == 0){
        return testCreateArrayList() ? 0 : 129;
    }
    if (strcmp(argv[1], "testGetUniqueGenres") == 0 || strcmp(argv[1], "7") == 0){
        return testCreateArrayList() ? 0 : 129;
    }

    return 214;
   
}