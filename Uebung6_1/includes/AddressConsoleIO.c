#include <stdio.h>
#include <stdlib.h>
#include "AddressConsoleIO.h"
#include "Address.h"

char InputBuffer[USERINPUT_BUFFER_SIZE];

void showMainMenue(int addressCounter){
    system("cls");
    printf("-------------------------------------------------------------------------------");
    printf("\n ADRESSVERWALTUNG                                     Adrian Kauz (2017.04.14)");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n Current entries: %i", addressCounter);
    printf("\n\n N --> New address");
    printf("\n L --> List adresses");
    printf("\n R --> Read addresses from file");
    printf("\n S --> Save addresses to file");
    printf("\n 1 --> Sort list by name");
    printf("\n 2 --> Sort list by street");
    printf("\n 3 --> Sort list by city");
    printf("\n Q --> Quit");
    printf("\n\n Your input: ");
}

struct tAddress* getNewAddressFromConsole(){
    struct tAddress* pNewPerson = malloc(sizeof(struct tAddress));

    if(pNewPerson != NULL){
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
        pNewPerson -> next = NULL;
        pNewPerson -> prev = NULL;
    }

    return pNewPerson;
}

char* getLine(){
    int charCounter = 0;

    // Read userinput into buffer
    InputBuffer[charCounter] = getchar();

    //while((isalnum(InputBuffer[charCounter]) || InputBuffer[charCounter] == ' ') && (charCounter < USERINPUT_BUFFER_SIZE)){
    while(isValidChar(InputBuffer[charCounter]) && (charCounter < USERINPUT_BUFFER_SIZE)){

        InputBuffer[++charCounter] = getchar();

        if(InputBuffer[charCounter] == '\n'){
            break;
        }
    }

    InputBuffer[charCounter] = '\0';

    // Allocate memory with the length of the input and copy the string from Buffer
    char* pNewString = (char*) malloc((charCounter + 1) * sizeof(char));

    int x = 0;
    for(x ; x <= charCounter ; x++){
        *(pNewString + x) = InputBuffer[x];
    }

    fflush(stdin);

    return pNewString;
}

int isValidChar(char newChar){
    // Remember: char is signed 8-Bit int!

    // Small Alphas
    if((96 < newChar) && (newChar < 123)){
        return 1;
    }

    // Big Alphas
    if((64 < newChar) && (newChar < 91)){
        return 1;
    }

    // Space
    if(newChar == 32){
        return 1;
    }

    // Digit
    if((47 < newChar) && (newChar < 58)){
        return 1;
    }

    // Minus sign
    if(45 == newChar){
        return 1;
    }

    return 0;
}
