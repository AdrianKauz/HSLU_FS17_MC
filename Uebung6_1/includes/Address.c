#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Address.h"
#include "AddressConsoleIO.h"
#include "AddressFileIO.h"

struct tAddress* pAddressList = NULL;

void startAddressManager(){
    int managerIsRunning = TRUE;

    do{
        char c;

        do{
            showMainMenue(countAddressList());
        } while(!isalnum(c = getchar()));

        fflush(stdin);
        c = toupper(c);

        switch(c){
            case 'A':
                pAddressList = addNewAddressToList(pAddressList, getNewAddressFromConsole());
                break;
            case 'L':
                // List addresses
                showAllAddresses(pAddressList);
                break;
            case 'R':
                // Read addresses from file
                pAddressList = importFromFile();
                printf("-------------------------------------------------------------------------------");
                printf("\n %d addresses are loaded.", countAddressList());
                printf("\n Press <Enter> to continue...");
                getchar();
                fflush(stdin);
                break;
            case 'S':
                // Save addresses to file
                exportToFile(pAddressList);
                printf("-------------------------------------------------------------------------------");
                printf("\n %d addresses saved.", countAddressList());
                printf("\n Press <Enter> to continue...");
                getchar();
                fflush(stdin);
                break;
            case '1':
                // Sort list by name
                break;
            case '2':
                // Sort list by street
                break;
            case '3':
                // Sort list by city
                break;
            case 'Q':
                // Quit
                managerIsRunning = FALSE;
                break;
            default:
                break;
        }
    }while(managerIsRunning);

    return;
}


struct tAddress* getNewEmptyAddressItem(){
    struct tAddress* pNewAddressItem = (struct tAddress*) malloc(sizeof(struct tAddress));
    pNewAddressItem -> hash = 0;
    pNewAddressItem -> next = NULL;
    pNewAddressItem -> prev = NULL;

    return pNewAddressItem;
}


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


struct tAddress* addNewAddressToList(struct tAddress* pCurrentAddressList, struct tAddress* pNewAddressItem){
    if(pNewAddressItem != NULL){
        if(pCurrentAddressList == NULL){
            pCurrentAddressList = pNewAddressItem;
        }
        else {
            // At first, find last element
            struct tAddress* pCurrAddress = pCurrentAddressList;

            // Searching...
            while(pCurrAddress -> next != NULL){
                pCurrAddress = pCurrAddress -> next;
            }

            // ...if found append new element to list
            pCurrAddress -> next = pNewAddressItem;
            pNewAddressItem -> prev = pCurrAddress;
        }
    }

    return pCurrentAddressList;
}

int countAddressList(){
    int addressCounter = 0;

    if(pAddressList != NULL){
        struct tAddress* currNode = pAddressList;

        while(currNode != NULL){
            addressCounter++;
            currNode = currNode -> next;
        }
    }

    return addressCounter;
}