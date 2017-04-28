/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 6.1
 * GUI-Functions
 *
 * @author Adrian Kauz
 * @version 0.9
 * @date 2017.04.28
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Address.h"
#include "AddressConsoleIO.h"

/*
================
showMainMenue()
================
*/
void showMainMenue(int addressCounter) {
    system("cls");
    printf("-------------------------------------------------------------------------------");
    printf("\n ADDRESSMANAGEMENT                                     Adrian Kauz (2017.04.28)");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n Current loaded addresses: %i", addressCounter);
    printf("\n\n   [A] Add new address");


    if(0 < addressCounter){
        printf("\n   [C] Remove address");
        printf("\n   [L] List all addresses");
        printf("\n");
    }

    printf("\n   [R] Read addresses from file");

    if(0 < addressCounter){
        printf("\n   [S] Save addresses to file");
        printf("\n");
    }

    if(1 < addressCounter){
        printf("\n   [1] Sort list by firstname");
        printf("\n   [2] Sort list by name");
        printf("\n   [3] Sort list by street");
        printf("\n   [4] Sort list by city");
        printf("\n");
    }

    printf("\n   [Q] Quit");
    printf("\n\n Selected option: ");
}

/*
================
startAddressManager()
================
*/
void startAddressManager(void) {
    int managerIsRunning = TRUE;
    int addressCounter;
    char c;

    do {
        addressCounter = lengthOfAddressList();

        do {
            showMainMenue(addressCounter);
        } while (!isalnum(c = getchar()));

        fflush(stdin);
        c = toupper(c);

        switch (c) {
            case 'A':
                printf("-------------------------------------------------------------------------------");
                if(addNewAddressToList(getNewAddressFromConsole()) == RET_SUCCESS){
                    printf("\n --> Address successfully added!");
                } else {
                    printf("\n --> ERROR: Unable to add the new address!");
                }

                showPressEnterToContinue();
                break;
            case 'C':
                // Remove an address
                if(0 < addressCounter) {
                    printf("-------------------------------------------------------------------------------");
                    printf("\n --> Option is not available at the moment!");
                    showPressEnterToContinue();
                }

                break;
            case 'L':
                // List addresses
                if(0 < addressCounter) {
                    printf("-------------------------------------------------------------------------------");
                    showAllAddresses(getCurrentAddressList());
                    showPressEnterToContinue();
                }

                break;
            case 'R':
                printf("-------------------------------------------------------------------------------");
                // Remember number of addresses before import
                int tempCounter = addressCounter;

                // Read addresses from file
                switch (importFromFile(CSV)){
                    case RET_FILE_IS_EMPTY:
                        printf("\n --> No addresses were imported. File was empty!");
                        break;
                    case RET_SUCCESS:
                        addressCounter = lengthOfAddressList();

                        // Calc difference of addresses before and after
                        tempCounter = addressCounter - tempCounter;

                        switch(tempCounter){
                            case 0:
                                printf("\n --> No new addresses were found!");
                                break;
                            case 1:
                                printf("\n --> 1 new address was successfully loaded!");
                                break;
                            default:
                                printf("\n --> %d new addresses were successfully loaded!", tempCounter);
                                break;
                        }
                        break;
                    case RET_FILE_NOT_FOUND:
                        printf("\n --> ERROR: File not Found!");
                        break;
                    default:
                        break;
                }

                showPressEnterToContinue();
                break;
            case 'S':
                printf("-------------------------------------------------------------------------------");
                // Save addresses to file
                if(0 < addressCounter){
                    switch(exportToFile(CSV)) {
                        case RET_SUCCESS:
                            if(addressCounter == 1) {
                                printf("\n --> 1 address was saved.");
                            } else {
                                printf("\n --> %d addresses were saved.", addressCounter);
                            }

                            break;
                        case RET_FILE_NOT_CREATED:
                            printf("\n --> Could not create file");
                            break;
                        default:
                            break;
                    }

                    showPressEnterToContinue();
                }

                break;
            case '1':
                // Sort list by firstname
                if(0 < addressCounter){
                    sortAddressList(FIRSTNAME);
                }

                break;
            case '2':
                // Sort list by name
                if(0 < addressCounter){
                    sortAddressList(NAME);
                }

                break;
            case '3':
                // Sort list by street
                if(0 < addressCounter){
                    sortAddressList(STREET);
                }

                break;
            case '4':
                // Sort list by city
                if(0 < addressCounter){
                    sortAddressList(CITY);
                }

                break;
            case 'Q':
                // Quit
                managerIsRunning = FALSE;
                break;
            default:
                break;
        }
    } while(managerIsRunning);

    return;
}

/*
================
getNewAddressFromConsole()
================
*/
struct tAddress* getNewAddressFromConsole(void) {
    struct tAddress* pNewPerson = getNewEmptyAddressItem();

    if(pNewPerson == NULL) {
        printf("\n Wasn't able to allocate new memory!");
    }
    else {
        printf("\n\n   Please insert new address (A-Z, a-z, 0-9, -):");
        printf("\n   ---------------------------------------------");
        printf("\n   Firstname: ");
        pNewPerson -> firstName = getString();
        printf("   Name:      ");
        pNewPerson -> name = getString();
        printf("   Street:    ");
        pNewPerson -> street = getString();
        printf("   StreetNr.: ");
        pNewPerson -> streetNr = getString();
        printf("   Zip:       ");
        pNewPerson -> zip = getString();
        printf("   City:      ");
        pNewPerson -> city = getString();
        printf("   ---------------------------------------------\n");

        calcHashForAddressItem(pNewPerson);
    }

    return pNewPerson;
}

/*
================
getLine()
================
*/
char* getString(void) {
    char Buffer[BUFFER_SIZE];
    int charCounter = 0;

    // Read userinput into buffer
    Buffer[charCounter] = getchar();

    while(isValidChar(Buffer[charCounter]) && (charCounter < BUFFER_SIZE)){

        Buffer[++charCounter] = getchar();

        if(Buffer[charCounter] == '\n'){
            break;
        }
    }

    fflush(stdin);
    Buffer[charCounter++] = '\0';

    return getStringFromBuffer(Buffer, charCounter);
}

/*
================
isValidChar()
================
*/
int isValidChar(char newChar) {
    // Remember: char is signed 8-Bit int!

    // Small Alphas
    if ((96 < newChar) && (newChar < 123)){
        return TRUE;
    }

    // Big Alphas
    if ((64 < newChar) && (newChar < 91)){
        return TRUE;
    }

    // Space
    if (newChar == 32){
        return TRUE;
    }

    // Digit
    if ((47 < newChar) && (newChar < 58)){
        return TRUE;
    }

    // Minus sign
    if (45 == newChar){
        return TRUE;
    }

    return FALSE;
}

/*
================
showAllAddresses()
================
*/
void showAllAddresses(struct tAddress* pCurrentAddress) {
    int addressCounter = 0;

    if (pCurrentAddress != NULL){

        do {
            printf("\n   %i)\t%s %s, %s %s, %s %s",
                   ++addressCounter,
                   pCurrentAddress -> firstName,
                   pCurrentAddress -> name,
                   pCurrentAddress -> street,
                   pCurrentAddress -> streetNr,
                   pCurrentAddress -> zip,
                   pCurrentAddress -> city);

            pCurrentAddress = pCurrentAddress -> next;
        } while (pCurrentAddress != NULL);
    };
}

/*
================
showPressEnterToContinue()
================
*/
void showPressEnterToContinue(void) {
    printf("\n\n Press <Enter> to continue...");
    getchar();
    fflush(stdin);

    return;
}