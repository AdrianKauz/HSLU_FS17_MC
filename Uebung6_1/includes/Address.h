#ifndef UEBUNG6_1_ADDRESS_H
#define UEBUNG6_1_ADDRESS_H

#define FALSE   0
#define TRUE    1

struct tAddress{
    char* firstName;
    char* name;
    char* street;
    char* streetNr;
    char* zip;
    char* city;
    struct tAddress* next;
    struct tAddress* prev;
};

void startAddressManager();
void addNewAddressToList(struct tAddress* newAddress);
int countAddressList();

#endif //UEBUNG6_1_ADDRESS_H
