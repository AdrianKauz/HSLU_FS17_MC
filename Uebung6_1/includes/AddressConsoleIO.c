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
    printf("\n L --> List all adresses");
    printf("\n R --> Read addresses from file");
    printf("\n S --> Save addresses to file");
    printf("\n 1 --> Sort list by name");
    printf("\n 2 --> Sort list by street");
    printf("\n 3 --> Sort list by city");
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

    Buffer[charCounter] = '\0';

    // Allocate memory with the length of the input and copy the string from Buffer
    char* pNewString = (char*) malloc((charCounter + 1) * sizeof(char));

    int x = 0;
    for(x ; x <= charCounter ; x++){
        *(pNewString + x) = Buffer[x];
    }

    fflush(stdin);

    return pNewString;
}

int isValidChar(char newChar){
    // Remember: char is signed 8-Bit int!

    // Small Alphas
    if((96 < newChar) && (newChar < 123)){
        return TRUE;
    }

    // Big Alphas
    if((64 < newChar) && (newChar < 91)){
        return TRUE;
    }

    // Space
    if(newChar == 32){
        return TRUE;
    }

    // Digit
    if((47 < newChar) && (newChar < 58)){
        return TRUE;
    }

    // Minus sign
    if(45 == newChar){
        return TRUE;
    }

    return FALSE;
}

void showAllAddresses(struct tAddress* pCurrentAddress){
    int addressCounter = 0;

    if(pCurrentAddress != NULL){
        printf("\n Nr.\tKey         Value");

        do{
            printf("\n-----------------------------------------------------------------");
            printf("\n %i)\tFirstname:  %s",++addressCounter, pCurrentAddress -> firstName);
            printf("\n\tName:       %s", pCurrentAddress -> name);
            printf("\n\tStreet:     %s", pCurrentAddress -> street);
            printf("\n\tStreetNr.:  %s", pCurrentAddress -> streetNr);
            printf("\n\tZip:        %s", pCurrentAddress -> zip);
            printf("\n\tCity:       %s", pCurrentAddress -> city);
            printf("\n\tHash:       %u", pCurrentAddress -> hash);

            pCurrentAddress = pCurrentAddress -> next;
        }while(pCurrentAddress != NULL);
    }

    printf("\n\n Press <Enter> to continue...");
    getchar();

    return;
}
