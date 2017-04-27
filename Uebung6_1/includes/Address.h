#ifndef UEBUNG6_1_ADDRESS_H
#define UEBUNG6_1_ADDRESS_H

#define BUFFER_SIZE 50

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
    CSV,
    TXT,
    XML,
    JSON
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
 * Adds a new address item into the list.
 *
 * @author  Adrian Kauz
 * @param   Calculated hash value.
 * @return  Returncode RET_SUCCESS or RET_FAILURE
 */
eReturnCode_t addNewAddressToList(struct tAddress*);


/**
 * Sort the address list by category.
 *
 * @author  Adrian Kauz
 * @param   eCategory-Enum: FIRSTNAME, NAME, STREET or CITY
 * @return  Integer if everything's OK or not. Better with Returncode enum.
 */
int sortAddressList(eCategory_t);


/**
 * Swap two address items.
 *
 * @author  Adrian Kauz
 * @param   The two address items to swap.
 */
void swapItems(struct tAddress*, struct tAddress*);


/**
 * Copy the string from the buffer into a new allocated memory.
 * After that, buffer is ready to receive a new string.
 *
 * @author  Adrian Kauz
 * @param   Pointer of the buffer, length of the string.
 * @return  Pointer of new allocated string.
 */
char* getStringFromBuffer(char* buffer, int len);


/**
 * Gets the requested import-filetype and calls the specific import-function.
 *
 * @author  Adrian Kauz
 * @param   Requested filetype as enum.
 * @return  Returncode RET_FILE_NOT_FOUND, RET_FILE_IS_EMPTY or RET_SUCCESS
 */
eReturnCode_t importFromFile(eFileType_t);


/**
 * Gets the requested export-filetype and calls the specific export-function.
 *
 * @author  Adrian Kauz
 * @param   Requested filetype as enum.
 * @return  Returncode is a simple integer at the moment. Better with Returncode.
 */
int exportToFile(eFileType_t);

#endif //UEBUNG6_1_ADDRESS_H
