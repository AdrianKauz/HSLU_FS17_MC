#ifndef UEBUNG6_1_ADDRESS_H
#define UEBUNG6_1_ADDRESS_H

enum boolean {FALSE, TRUE};
enum sortItem {FIRSTNAME, NAME, STREET, ZIP, CITY} item;

struct tAddress{
    char* firstName;
    char* name;
    char* street;
    char* streetNr;
    char* zip;
    char* city;
    unsigned int hash;
    struct tAddress* next;
    struct tAddress* prev;
};

void startAddressManager();
struct tAddress* getNewEmptyAddressItem();
void calcHashForAddressItem(struct tAddress*);
unsigned int jenkins_one_at_a_time_hash(const char*);
struct tAddress* addNewAddressToList(struct tAddress*, struct tAddress*);
int countAddressList();
struct tAddress* sortAddressListByName(struct tAddress*, size_t);
void swapItems(struct tAddress*, struct tAddress*);

#endif //UEBUNG6_1_ADDRESS_H
