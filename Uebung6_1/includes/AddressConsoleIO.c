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
    printf("\n ADDRESSMANAGEMENT                                     Adrian Kauz (2017.04.14)");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n Current entries: %i", addressCounter);
    printf("\n\n   [A] Add new address");

    if(0 < addressCounter){
        printf("\n   [L] List all addresses");
    }

    printf("\n   [R] Read addresses from file");

    if(0 < addressCounter){
        printf("\n   [S] Save addresses to file");
    }

    if(1 < addressCounter){
        printf("\n   [1] Sort list by firstname");
        printf("\n   [2] Sort list by name");
        printf("\n   [3] Sort list by street");
        printf("\n   [4] Sort list by city");
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
            case 'L':
                printf("-------------------------------------------------------------------------------");
                // List addresses
                if(0 < addressCounter){
                    showAllAddresses(getCurrentAddressList());
                    showPressEnterToContinue();
                }

                break;
            case 'R':
                printf("-------------------------------------------------------------------------------");
                // Read addresses from file
                switch (importFromFile(CSV)){
                    case RET_FILE_IS_EMPTY:
                        printf("\n --> No addresses were imported. File was empty!");
                        break;
                    case RET_SUCCESS:
                        addressCounter = lengthOfAddressList();

                        if(addressCounter < 2){
                            printf("\n --> 1 address was successfully loaded!", addressCounter);
                        } else {
                            printf("\n --> %d addresses were successfully loaded!", addressCounter);
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
                    exportToFile(CSV);
                    printf("-------------------------------------------------------------------------------");
                    printf("\n %d addresses saved.", addressCounter);
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
    } while (managerIsRunning);

    return;
}

/*
================
getNewAddressFromConsole()
================
*/
struct tAddress* getNewAddressFromConsole(void) {
    struct tAddress* pNewPerson = getNewEmptyAddressItem();

    if(pNewPerson == NULL){
        printf("\n Wasn't able to allocate new memory!");
    }
    else{
        printf("\n\n   Please insert new address (A-Z, a-z, 0-9, -):");
        printf("\n   ---------------------------------------------");
        printf("\n   Firstname: ");
        pNewPerson -> firstName = getLine();
        printf("   Name:      ");
        pNewPerson -> name = getLine();
        printf("   Street:    ");
        pNewPerson -> street = getLine();
        printf("   StreetNr.: ");
        pNewPerson -> streetNr = getLine();
        printf("   Zip:       ");
        pNewPerson -> zip = getLine();
        printf("   City:      ");
        pNewPerson -> city = getLine();
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
char* getLine(void) {
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