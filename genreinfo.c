#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "songinfo.h"
#include "genreinfo.h"

void generateUniqueGenresLL(LLNode ** headPP, ArrayList_of_Songs songList){
    // call getUniqueGenres
    char **genreList;
    int genreListSize=0;
    getUniqueGenres(songList,&genreList,&genreListSize);
    // call createLLFromList
    createLLFromList(headPP,genreList,genreListSize);
    // call countSongsInEachGenre
    countSongsInEachGenre(*headPP,songList);
}


void getUniqueGenres(ArrayList_of_Songs songList, char *** genreListPtr, int * genreListSize){
    int capacity = 2;       // do not change initial capacity.
    const int GROW_BY = 2;  // use GROW_BY for the adjustment to capacity
                            // **EXAMPLE:**
                            //    capacity += GROW_BY;
                            //    
                            
    char ** genreList; // use this to build genreList then the function sets it to the triple pointer at the end 
    // CODE: INSERT genreList creation code here
    genreList=malloc(sizeof(char *) * capacity);
    genreList[0]=strdup(songList.songs[0].genre);
    int index=1;
    *genreListSize=1;
    for(int i=0;i<songList.count;++i){
        int j=0;
        int repeatedGenre=0;
        while (j<*genreListSize)
        {
            if(strcmp(songList.songs[i].genre,genreList[j])==0){
                repeatedGenre+=1;
                break;
            }    
            ++j;
        }
        if(repeatedGenre<=0){
        genreList = realloc(genreList, sizeof(char *) * capacity);
        capacity+=GROW_BY;
        genreList[index]=strdup(songList.songs[i].genre);
        *genreListSize+=1;
        index+=1;
        }  
    }
    *genreListPtr = genreList; // setting the address of genreListPtr so that it will be returned to calling function
}   

void createLLFromList(LLNode ** uniqueGenreLLPtr, char ** genreList, int genreNameCount){
    // commented out to aid compiling eaarly
    LLNode * head = NULL;  // starting with it at NULL is important 
    LLNode *current;
    current = head;
    // CODE: INSERT code that creates the linked list, keep the list in the same order as the genreList entries    
    GenreInfo gi;
    for(int i=0;i<genreNameCount;++i){
        gi.genreName=genreList[i];
        LLNode *Node=createLinkedListNode(gi);
        if(head==NULL){
            head=Node;
            current=head;
        }
        else {
            current->next=Node;
            current=current->next;
        }
    }
    // CODE: The code needs to return the address held in the pointer head to the double pointer.
    //       The double pointer allows us to change the address used by the calling function even though 
    //       it's pass by value
    *uniqueGenreLLPtr = head;
}

void countSongsInEachGenre(LLNode * uniqueGenreLL, ArrayList_of_Songs songList){
    while (uniqueGenreLL!=NULL)
    {
        uniqueGenreLL->gi.songCount=0;
        for(int i=0;i<songList.count;++i){
            if(strcmp(songList.songs[i].genre,uniqueGenreLL->gi.genreName)==0){
                uniqueGenreLL->gi.songCount++;
            }
        }
        uniqueGenreLL=uniqueGenreLL->next;
    }
}

// Initialize the LinkedListNode
LLNode * createLinkedListNode(GenreInfo gi) {    
    
    // CODE: newNode malloc 
    LLNode * newNode = malloc(sizeof(LLNode));
    if (!newNode) {
        printf("Failed to allocate memory for node.\n");
        exit(EXIT_FAILURE);
    }
    
    // CODE: set newNode's device 
    newNode->gi = gi;
    // CODE: set next equal to NULL
    newNode->next = NULL;
    
    return newNode;

}

// Add an item to the end of the list (replacing next->NULL)
// Uses double pointer because the first node can change
void addLinkedListNodeToEnd(LLNode **headPP, GenreInfo gi){
    LLNode * head = *headPP;
    // if no nodes (head == NULL) then create  a newNode and set it
     if (head == NULL){
        // CODE: *headPP = newly created node
        *headPP = createLinkedListNode(gi);
        return; // skips to the end
    } 
    LLNode *current = head;


    // CODE: find the end of the list use while next is not null, 
        // CODE current = next
        while(current->next!=NULL){
         current = current->next;   
        }

    
    // head -> 0 -> 1 -> 2 -> NULL  add 3 to end, head -> 0 -> 1 -> 2 -> 3 -> NULL
    // CODE: create a new Node and set to current's next  
    current->next=createLinkedListNode(gi);
    *headPP = head; // returning head to *headPP
}

// Retrieve an item from the LinkedListNode
LLNode * getElementLinkedList(LLNode *head, size_t index) {
    LLNode* temp = head;
    int count = 0;
    // CODE: create while loop that loops through list while the current element is not null and count is less than index
    // can be a for loop or while loop
    for(count=0;count<index && temp != NULL; count++){
        temp=temp->next;
    }
    // if not found or index < 0 then invalid index and exit
    if (!temp || index < 0) { 
        printf("Invalid index %ld.\n", index);
        exit(99); // made up non-zero number
    }
    return temp;
}

// Clean up the LinkedList Items
void freeLinkedList(LLNode *head) {

    LLNode* nodeToBeFreed;
    while (head != NULL){
        nodeToBeFreed=head;
        head=head->next;
        free(nodeToBeFreed);
    }    
}

void printGenres(LLNode *head) {    
    // CODE: create current pointer and set to head 
    LLNode *current = head; 
    // CODE: print linked list %s ->    
    while (current!=NULL){    
        printf("%-10s %d\n", current->gi.genreName, current->gi.songCount);  
        current=current->next;  
    }  
}   
