/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 3.1
 * Get name and forename via console from the user and save the values
 * as a simple list.
 * Still full with bugs! Bleh!
 * @author Adrian Kauz
 * @version 0.5
 * @date 2017.03.28
 * @return 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BLOCK_SIZE = 10;

struct tPerson{
    char* forename;
    char* surname;
    struct tPerson* next;
    struct tPerson* prev;
};


struct tPerson* fillListWithNames(struct tPerson* newList);
void printList(struct tPerson* newList);
char* readString(char* pText);
struct tPerson* addElementToList(struct tPerson* currList, struct tPerson* newElement);
struct tPerson* generateNewElement(char* newUserInput, int* newUserInputLength);


int main() {
    struct tPerson* list = NULL;

    system("cls");
    printList(fillListWithNames(list));

    return(EXIT_SUCCESS);
}

/**
 * Fills a list with persons by their names
 * First variant is handling simple names like "Foo Bar" or "Jean-Luc Piccard".
 * @author Adrian Kauz
 * @param Empty pointer to the list
 * @return Nothing
 */
struct tPerson* fillListWithNames(struct tPerson* currList){
    char* userInput;
    size_t stringLength;

    printf("\nAdd a person. Forename first, surname second.\n"
                   "Press <Enter> when finish.\n");
    do{
        printf("--> " );
        userInput = readString(userInput);
        stringLength = strlen(userInput);

        if(stringLength > 0){
            currList = addElementToList(currList, generateNewElement(userInput, &stringLength));
        }

        free(userInput);
    }
    while(stringLength > 0);

    return currList;
}


/**
 * Adds new element into the linked list
 * @author Adrian Kauz
 * @param Current list
 * @param Pointer to new person-element
 * @return Updated list
 */
struct tPerson* addElementToList(struct tPerson* pCurrList, struct tPerson* pNewElement){
    if(pCurrList == NULL){
        pCurrList = pNewElement;
        pCurrList -> next = NULL;
        pCurrList -> prev = NULL;
    }
    else{
        // At first, find last element
        struct tPerson* pCurrElement = pCurrList; // get first element from list

        // Searching...
        while(pCurrElement -> next != NULL){
            pCurrElement = pCurrElement -> next;
        }

        // ...if found append new element to list
        pCurrElement -> next = pNewElement;
        pNewElement -> prev = pCurrElement;
    }

    return pCurrList;
}


/**
 * Convert user's input into a person-struct.
 * @author Adrian Kauz
 * @param Empty Pointer
 * @return Pointer with all the characters from console
 */
struct tPerson* generateNewElement(char* newUserInput, int* newUserInputLength){
    // At first, search for whitespace...
    int lengthOfForename = 0;

    int x = 0;
    for(x ; x < *newUserInputLength; x++){
        if(*(newUserInput + x) == ' '){
            lengthOfForename = x;
            break;
        }
    }

    // Then generate new element
    struct tPerson* pNewPerson = malloc(sizeof(struct tPerson));
    pNewPerson -> forename = (char *) malloc(sizeof(char) * (lengthOfForename + 1));
    pNewPerson -> surname = (char *) malloc(sizeof(char) * (*newUserInputLength - lengthOfForename));
    pNewPerson -> next = NULL;
    pNewPerson -> prev = NULL;

    int isPartOfForename = 1;
    for(x = 0 ; x <= *newUserInputLength ; x++){
        if(isPartOfForename){
            if(*(newUserInput + x) == ' '){
                isPartOfForename = 0;
                *(pNewPerson -> forename + x) = '\0';
            }
            else{
                *(pNewPerson -> forename + x) = *(newUserInput + x);
            }
        }
        else{
            *(pNewPerson -> surname + x - lengthOfForename - 1) = *(newUserInput + x);
        }
    }

    return pNewPerson;
}


/**
 * Reads input-stream from console. Memory is dynamically allocated.
 * @author Adrian Kauz
 * @param Empty Pointer
 * @return Pointer with all the characters from console
 */
char* readString(char* pText){
    int i = 0;
    char c;

    //Initial the first memoryblock
    pText = (char *) malloc(sizeof(char) * BLOCK_SIZE);

    if(pText){
        while ((c = getchar()) != EOF && c != '\n'){
            *(pText + i) = c;
            i++;

            if(i % BLOCK_SIZE == 0){
                //Extend current memory with another block
                pText = (char *) realloc(pText, sizeof(char) * (i + BLOCK_SIZE));

                if (!pText){
                    break;
                }
            }
        }

        *(pText + i) = '\0';
    }

    return pText;
}


/**
 * Prints out the values of a struct-person-list
 * @author Adrian Kauz
 * @param List with struct-person elements
 * @return Nothing
 */
void printList(struct tPerson* newList){
    printf("\nResult of your input\n");
    printf("--------------------");

    struct tPerson* currElement = newList;

    int validNextLoop = 1;
    do{
        if(currElement -> next == NULL){
            validNextLoop = 0;
        }

        printf("\n- %s %s", currElement-> forename, currElement-> surname);
        currElement = currElement -> next;
    }
    while(validNextLoop);

    return;
}