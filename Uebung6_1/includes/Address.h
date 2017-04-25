#ifndef UEBUNG6_1_ADDRESS_H
#define UEBUNG6_1_ADDRESS_H

enum eBoolean {FALSE, TRUE};
enum eCategory {FIRSTNAME, NAME, STREET, ZIP, CITY} eCategory_t;

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
struct tAddress* sortAddressListByName(struct tAddress*, enum eCategory);
void swapItems(struct tAddress*, struct tAddress*);
char* getStringFromBuffer(char* buffer, int len);

#endif //UEBUNG6_1_ADDRESS_H
