#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Address.h"
#include "AddressConsoleIO.h"
#include "AddressFileIO.h"

struct tAddress* pAddressList = NULL;

/*
================
getCurrentAddressList()
================
*/
struct tAddress* getCurrentAddressList(void){
    return pAddressList;
}

/*
================
lengthOfAddressList()
================
*/
int lengthOfAddressList(void){
    int addressCounter = 0;

    if (pAddressList != NULL){
        struct tAddress* currNode = pAddressList;

        while (currNode != NULL){
            addressCounter++;
            currNode = currNode -> next;
        }
    }

    return addressCounter;
}

/*
================
getNewEmptyAddressItem()
================
*/
struct tAddress* getNewEmptyAddressItem(void){
    struct tAddress* pNewAddressItem = (struct tAddress*) malloc(sizeof(struct tAddress));

    if(pNewAddressItem != NULL){
        pNewAddressItem -> hash = 0;
        pNewAddressItem -> next = NULL;
        pNewAddressItem -> prev = NULL;
    }

    return pNewAddressItem;
}

/*
================
calcHashForAddressItem()
================
*/
void calcHashForAddressItem(struct tAddress* pAddressItem){
    unsigned int hash = 0;
    hash += jenkins_one_at_a_time_hash(pAddressItem -> firstName);
    hash += jenkins_one_at_a_time_hash(pAddressItem -> name);
    hash += jenkins_one_at_a_time_hash(pAddressItem -> street);
    hash += jenkins_one_at_a_time_hash(pAddressItem -> streetNr);
    hash += jenkins_one_at_a_time_hash(pAddressItem -> zip);
    hash += jenkins_one_at_a_time_hash(pAddressItem -> city);
    pAddressItem -> hash = hash;
}

/*
================
jenkins_one_at_a_time_hash()
================
*/
unsigned int jenkins_one_at_a_time_hash(const char* key) {
    size_t stringLength = strlen(key);
    size_t x = 0;
    unsigned int hash = 0;

    while (x != stringLength) {
        hash += key[x++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return hash;
}

/*
================
addNewAddressToList()
================
*/
eReturnCode_t addNewAddressToList(struct tAddress* pNewAddressItem){
    if (pNewAddressItem != NULL){
        if (pAddressList == NULL){
            pAddressList = pNewAddressItem;
        } else {
            // At first, find last element
            struct tAddress* pCurrAddress = pAddressList;

            // Searching...
            while (pCurrAddress -> next != NULL){
                pCurrAddress = pCurrAddress -> next;
            }

            // ...if found append new element to list
            pCurrAddress -> next = pNewAddressItem;
            pNewAddressItem -> prev = pCurrAddress;
        }

        return RET_SUCCESS;
    }

    return RET_FAILURE;
}

/*
================
sortAddressList()
================
*/
int sortAddressList(eCategory_t category){
    // Used algorithm: Bubblesort
    if(pAddressList != NULL){
        if(pAddressList -> next != NULL){
            int x;
            int strcmpResult;
            int requestedLoop = TRUE;
            struct tAddress* currItem;
            struct tAddress* nextItem;

            while(requestedLoop){
                requestedLoop = FALSE;
                currItem = pAddressList;
                nextItem = currItem -> next;

                x = 0;
                while(nextItem != NULL){
                    switch (category){
                        case FIRSTNAME:
                            strcmpResult = strcmp(currItem -> firstName, nextItem -> firstName);
                            break;
                        case NAME:
                            strcmpResult = strcmp(currItem -> name, nextItem -> name);
                            break;
                        case STREET:
                            strcmpResult = strcmp(currItem -> street, nextItem -> street);
                            break;
                        case CITY:
                            strcmpResult = strcmp(currItem -> city, nextItem -> city);
                            break;
                        default:
                            break;
                    };

                    if(strcmpResult > 0){
                        swapItems(currItem, nextItem);

                        // Next-Item is know the first item in the list
                        if(x == 0){
                            pAddressList = nextItem;
                        }

                        requestedLoop = TRUE;
                    } else {
                        currItem = currItem -> next;
                    }

                    nextItem = currItem -> next;
                    x++;
                }
            }
        }
    }

    return 1;
}

/*
================
swapItems()
================
*/
void swapItems(struct tAddress* pA, struct tAddress* pB){
    struct tAddress* temp = pA -> next;

    // At first update border node of the left node "pA"...
    if (pA -> prev != NULL) {
        pA -> prev -> next = pB;
    }

    // ...then update border node of the right node "pB"...
    if (pB -> next != NULL) {
        pB -> next -> prev = pA;
    }

    // ...aaaand finally swap pA and PB
    pA -> next = pB -> next;
    pB -> next = pB -> prev;
    pB -> prev = pA -> prev;
    pA -> prev = temp;
}

/*
================
getStringFromBuffer()
================
*/
char* getStringFromBuffer(char* buffer, int len){
    char* newItem = (char*) malloc(sizeof(char) * len);

    if(newItem != NULL){
        int x = 0;
        for(x ; x < len; x++){
            newItem[x] = buffer[x];
        }
    }

    return newItem;
}

/*
================
importFromFile()
================
*/
eReturnCode_t importFromFile(eFileType_t fileType){
    if(fileType == CSV){
        return importFromCSV();
    }

    // Maybe there is time for more import-types
    return RET_UNKNOWN_FILE_TYPE;
}

/*
================
exportToFile()
================
*/
int exportToFile(eFileType_t fileType){
    switch(fileType){
        case CSV:
            exportToCSV(pAddressList);
            break;
        default:
            break;
    }

    return 1;
}