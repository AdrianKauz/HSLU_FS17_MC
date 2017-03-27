/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 3.1
 * Get name and forename via console from the user and save the values
 * as a simple list
 * @author Adrian Kauz
 * @version 1.0
 * @date 2017.03.27
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
};

void fillListWithNames(struct tPerson* newList);
//void printList(struct tPerson* newList);
char* readString(char* pText);
struct tPerson* addElementToList(struct tPerson* currList, struct tPerson* newElement);
struct tPerson* getNewElement(char* newUserInput, int* newUserInputLength);

int main() {
    struct tPerson* list = NULL;

    fillListWithNames(list);
//printList(list);

    return(EXIT_SUCCESS);
}

/**
 * Fills a list with persons by their names
 * First variant is handling simple names like "Foo Bar" or "Jean-Luc Piccard".
 * @author Adrian Kauz
 * @param Empty pointer to the list
 * @return Nothing
 */
void fillListWithNames(struct tPerson* currList){
    char* userInput;
    size_t stringLength;

    do{
        printf("\nAdd a person. forename first, surname second: ");
        userInput = readString(userInput);
        stringLength = strlen(userInput);

        if(stringLength > 0){
            currList = addElementToList(currList, getNewElement(userInput, &stringLength));
            printf("%s", currList -> forename);
        }

        free(userInput);
    }
    while(stringLength > 0);

    return;
}


/**
 * Reads input-stream from console. Memory is dynamically allocated.
 * @author Adrian Kauz
 * @param Empty Pointer
 * @return Pointer with all the characters from console
 */
struct tPerson* addElementToList(struct tPerson* pCurrList, struct tPerson* pNewElement){
    if(pCurrList == NULL){
        pCurrList = malloc(sizeof(struct tPerson));
        *pCurrList = *pNewElement;
    }
    else{
        struct tPerson* pTempElement = pCurrList;

        while(pTempElement -> next){
            pTempElement = pTempElement -> next;
        }

        pTempElement -> next = pNewElement;

        //free(tempElement);
    }

    return pCurrList;
}


/**
 * Convert users input into an person-struct.
 * @author Adrian Kauz
 * @param Empty Pointer
 * @return Pointer with all the characters from console
 */
struct tPerson* getNewElement(char* newUserInput, int* newUserInputLength){
    struct tPerson* pNewPerson = malloc(sizeof(struct tPerson));

    //Search for whitespace
    int lengthOfForename = 0;

    int x = 0;
    for(x ; x < *newUserInputLength; x++){
        if(*(newUserInput + x) == ' '){
            lengthOfForename = x;
            break;
        }
    }

    pNewPerson -> forename = (char *) malloc(sizeof(char) * (lengthOfForename + 1));
    pNewPerson -> surname = (char *) malloc(sizeof(char) * (*newUserInputLength - lengthOfForename));
    pNewPerson -> next = NULL;

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
