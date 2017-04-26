#ifndef UEBUNG6_1_ADDRESS_H
#define UEBUNG6_1_ADDRESS_H

typedef enum eBoolean {
    FALSE,
    TRUE
} eBoolean_t;

typedef enum eCategory {
    FIRSTNAME,
    NAME,
    STREET,
    ZIP,
    CITY
} eCategory_t;

typedef enum eFileType {
    CSV
} eFileType_t;

typedef enum eReturnCode {
    RET_SUCCESS,
    RET_FAILURE,
    RET_FILE_NOT_FOUND,
    RET_FILE_IS_EMPTY,
    RET_UNKNOWN_FILE_TYPE
} eReturnCode_t;

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

/**
 * Returns pointer of current list of address-items.
 *
 * @author  Adrian Kauz
 * @return  current list of addresses as linked list
 */
struct tAddress* getCurrentAddressList(void);

/**
 * Returns the total number of address-items in the list.
 *
 * @author  Adrian Kauz
 * @return  Number of address-items of the linked list as integer
 */
int lengthOfAddressList(void);

/**
 * Returns a new empty address-item.
 *
 * @author  Adrian Kauz
 * @return  An empty address-item
 */
struct tAddress* getNewEmptyAddressItem(void);

/**
 * Calculate hash value for an address-item.
 * The hash-value will not be exported. It's only used internal to identify
 * duplicated items.
 *
 * @author  Adrian Kauz
 * @param   Pointer of the address-item which needs a hash.
 */
void calcHashForAddressItem(struct tAddress*);

/**
 * Calculates a hash value for a string.
 * Source: https://en.wikipedia.org/wiki/Jenkins_hash_function
 *
 * @author  Adrian Kauz
 * @param   Calculated hash value.
 */
unsigned int jenkins_one_at_a_time_hash(const char*);

/**
 * Calculates a hash value for a string.
 * Source: https://en.wikipedia.org/wiki/Jenkins_hash_function
 *
 * @author  Adrian Kauz
 * @param   Calculated hash value.
 * @return  Errorcode SUCCESS / FAILURE
 */
eReturnCode_t addNewAddressToList(struct tAddress*);


int                 sortAddressListByName(eCategory_t);
void                swapItems(struct tAddress*, struct tAddress*);
char*               getStringFromBuffer(char* buffer, int len);
eReturnCode_t                 importFromFile(eFileType_t);
int                 exportToFile(eFileType_t);

#endif //UEBUNG6_1_ADDRESS_H
