/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 6.1
 * Functions for handling the address list
 *
 * @author Adrian Kauz
 * @version 0.99
 * @date 2017.05.01
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Address.h"
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
        pNewAddressItem -> firstName = NULL;
        pNewAddressItem -> name = NULL;
        pNewAddressItem -> street = NULL;
        pNewAddressItem -> streetNr = NULL;
        pNewAddressItem -> zip = NULL;
        pNewAddressItem -> city = NULL;
        pNewAddressItem -> hash = 0;
        pNewAddressItem -> next = NULL;
        pNewAddressItem -> prev = NULL;
    }

    return pNewAddressItem;
}

/*
================
clearAddressItem()
================
*/
eReturnCode_t clearAddressItem(struct tAddress* pAddressItem){

    extendedFree(pAddressItem -> firstName);
    extendedFree(pAddressItem -> name);
    extendedFree(pAddressItem -> street);
    extendedFree(pAddressItem -> streetNr);
    extendedFree(pAddressItem -> zip);
    extendedFree(pAddressItem -> city);
    pAddressItem -> hash = 0;
    pAddressItem -> next = NULL;
    pAddressItem -> prev = NULL;

    return RET_SUCCESS;
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
addressAlreadyExists()
================
*/
eBoolean_t addressAlreadyExists(int currHashValue) {
    if (pAddressList != NULL){
        struct tAddress* pCurrAddress = pAddressList;

        do{
            if (pCurrAddress -> hash == currHashValue) {
                return TRUE;
            }
            else {
                pCurrAddress = pCurrAddress -> next;
            }
        } while(pCurrAddress != NULL);
    }

    return FALSE;
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
removeAddressFromList()
================
*/
eReturnCode_t removeAddressFromList(int length, int addressNumber) {
    if ((length > 0) && (addressNumber > 0) && (addressNumber <= length)) {
        struct tAddress* currAddressItem = pAddressList;
        unsigned int currItemNumber = 1;

        // Search item
        while (currAddressItem != NULL) {
            if(currItemNumber == addressNumber) {
                break;
            } else {
                currAddressItem = currAddressItem -> next;
                currItemNumber++;
            }
        }

        // At first decouple item from the list
        if (currItemNumber == 1) {
            if (length != 1) {
                pAddressList = currAddressItem -> next;
                pAddressList -> prev = NULL;
            }
        } else {
            if (currItemNumber == length) {
                currAddressItem -> prev -> next = NULL;
            } else {
                currAddressItem -> prev -> next = currAddressItem -> next;
                currAddressItem -> next -> prev = currAddressItem -> prev;
            }
        }

        // Then delete item
        extendedFree(currAddressItem -> firstName);
        extendedFree(currAddressItem -> name);
        extendedFree(currAddressItem -> street);
        extendedFree(currAddressItem -> streetNr);
        extendedFree(currAddressItem -> zip);
        extendedFree(currAddressItem -> city);
        extendedFree(currAddressItem);

        return RET_SUCCESS;
    }

    return RET_NOTHING_TO_REMOVE;
}

/*
================
sortAddressList()
================
*/
eReturnCode_t sortAddressList(eCategory_t category) {
    // Used algorithm: Bubblesort
    if(pAddressList != NULL){
        if(pAddressList -> next != NULL){
            int x = 0;
            int strcmpResult = 0;
            int requestedLoop = TRUE;
            struct tAddress* currItem;
            struct tAddress* nextItem;

            // Start sorting algorithm
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

            if (0 < x) {
                return RET_SUCCESS;
            }
        }
    }

    return RET_NOTHING_TO_SORT;
}

/*
================
swapItems()
================
*/
void swapItems(struct tAddress* pA, struct tAddress* pB) {
    /*    +--------+     +--------+     +--------+     +--------+
       +--|prev    |  +--|prev    |  +--|prev    |  +--|prev    |
          |  [pX]  |  |  | [pA]   |  |  | [pB]   |  |  | [pY]   |
          |    next|--+  |    next|--+  |    next|--+  |    next|--+
          +--------+     +--------+     +--------+     +--------+
    */
    struct tAddress* temp = pA -> next;

    // At first update border node of the outer left node "pX"...
    if (pA -> prev != NULL) {
        pA -> prev -> next = pB;
    }

    // At first update border node of the outer right node "pY"...
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
char* getStringFromBuffer(char* buffer, int len) {
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
eReturnCode_t importFromFile(eFileType_t fileType) {
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
eReturnCode_t exportToFile(eFileType_t fileType) {
    if(fileType == CSV){
        return exportToCSV(pAddressList);
    }

    return RET_UNKNOWN_FILE_TYPE;
}