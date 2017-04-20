#include <ctype.h>
#include <stdio.h>
#include "AddressConsoleIO.h"
#include "Address.h"

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
            case 'N':
                addNewAddressToList(getNewAddressFromConsole());
                break;
            case 'L':
                // List addresses
                showAllAddresses(pAddressList);
                break;
            case 'R':
                // Read addresses from file
                break;
            case 'S':
                // Save addresses to file
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

void addNewAddressToList(struct tAddress* pNewAddress){
    if(pNewAddress != NULL){
        if(pAddressList == NULL){
            pAddressList = pNewAddress;
        }
        else {
            // At first, find last element
            struct tAddress* pCurrAddress = pAddressList;

            // Searching...
            while(pCurrAddress -> next != NULL){
                pCurrAddress = pCurrAddress -> next;
            }

            // ...if found append new element to list
            pCurrAddress -> next = pNewAddress;
            pNewAddress -> prev = pCurrAddress;
        }
    }

    return;
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