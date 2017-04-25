#include <stdio.h>
#include <stdlib.h>
#include "Address.h"
#include "AddressConsoleIO.h"

void showMainMenue(int addressCounter){
    system("cls");
    printf("-------------------------------------------------------------------------------");
    printf("\n ADRESSVERWALTUNG                                     Adrian Kauz (2017.04.14)");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n Current entries: %i", addressCounter);
    printf("\n\n A --> Add new address");

    if(0 < addressCounter){
        printf("\n L --> List all adresses");
    }

    printf("\n R --> Read addresses from file");

    if(0 < addressCounter){
        printf("\n S --> Save addresses to file");
    }

    if(1 < addressCounter){
        printf("\n 1 --> Sort list by firstname");
        printf("\n 2 --> Sort list by name");
        printf("\n 3 --> Sort list by street");
        printf("\n 4 --> Sort list by city");
    }

    printf("\n Q --> Quit");
    printf("\n\n Your input: ");
}


struct tAddress* getNewAddressFromConsole(){
    struct tAddress* pNewPerson = getNewEmptyAddressItem();

    if(pNewPerson == NULL){
        printf("\n Wasn't able to allocate new memory!");
    }
    else{
        printf("\n ---------------------------------------------");
        printf("\n Please insert new address (A-Z, a-z, 0-9, -):");
        printf("\n ---------------------------------------------");
        printf("\n Firstname: ");
        pNewPerson -> firstName = getLine();
        printf(" Name: ");
        pNewPerson -> name = getLine();
        printf(" Street: ");
        pNewPerson -> street = getLine();
        printf(" StreetNr.: ");
        pNewPerson -> streetNr = getLine();
        printf(" Zip: ");
        pNewPerson -> zip = getLine();
        printf(" City: ");
        pNewPerson -> city = getLine();
        calcHashForAddressItem(pNewPerson);
    }

    return pNewPerson;
}


char* getLine(){
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


int isValidChar(char newChar){
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


void showAllAddresses(struct tAddress* pCurrentAddress){
    int addressCounter = 0;

    if (pCurrentAddress != NULL){
        printf("\n Nr.\tAddress");
        printf("\n ---\t-----------------------------------------------------------------------");

        do {
            printf("\n %i)\t%s %s, %s %s, %s %s",
                   ++addressCounter,
                   pCurrentAddress -> firstName,
                   pCurrentAddress -> name,
                   pCurrentAddress -> street,
                   pCurrentAddress -> streetNr,
                   pCurrentAddress -> zip,
                   pCurrentAddress -> city);

            pCurrentAddress = pCurrentAddress -> next;
        } while (pCurrentAddress != NULL);
    }

    printf("\n\n Press <Enter> to continue...");
    getchar();

    return;
}
