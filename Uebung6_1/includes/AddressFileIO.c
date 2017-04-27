//
// Created by Adrian Kauz on 22.04.2017.
//
#include <stdio.h>
#include "Address.h"
#include "AddressFileIO.h"

static const char SEPARATOR = ',';
static const char* FILENAME = "addresslist.csv";

/*
================
exportToCSV()
================
*/
int exportToCSV(struct tAddress* pAddressList){
    if(pAddressList != NULL){
        FILE* fp;
        fp = fopen(FILENAME, "w");

        if(fp != NULL){
            do{
                fprintf(fp, "%s%c%s%c%s%c%s%c%s%c%s\n",
                        pAddressList -> firstName,
                        SEPARATOR,
                        pAddressList -> name,
                        SEPARATOR,
                        pAddressList -> street,
                        SEPARATOR,
                        pAddressList -> streetNr,
                        SEPARATOR,
                        pAddressList -> zip,
                        SEPARATOR,
                        pAddressList -> city);

                pAddressList = pAddressList -> next;
            } while (pAddressList != NULL);

            fclose(fp);

            return 1;
        }
    }

    return 0;
}

/*
================
importFromCSV()
================
*/
eReturnCode_t importFromCSV(){
    int addressCounter = 0;
    FILE* fp;
    fp = fopen(FILENAME, "r");

    if(fp == NULL) {
        return RET_FILE_NOT_FOUND;
    }
    else {
        char Buffer[BUFFER_SIZE];
        char c;
        int charCounter = 0;
        int addressFragmentCounter = 0;
        struct tAddress* pNewAddressItem = getNewEmptyAddressItem();

        // Start parsing...
        // ---------------------------------------------------------------------
        while((c = getc(fp)) != EOF) {
            if (c != SEPARATOR && c != '\n') {
                Buffer[charCounter++] = c;
            } else {
                // End of address item. First add string terminator
                // ------------------------------------------------
                Buffer[charCounter++] = '\0';

                // Then add new string into address item
                // -------------------------------------
                switch (addressFragmentCounter) {
                    case 0:
                        pNewAddressItem->firstName = getStringFromBuffer(Buffer, charCounter);
                        break;
                    case 1:
                        pNewAddressItem->name = getStringFromBuffer(Buffer, charCounter);
                        break;
                    case 2:
                        pNewAddressItem->street = getStringFromBuffer(Buffer, charCounter);
                        break;
                    case 3:
                        pNewAddressItem->streetNr = getStringFromBuffer(Buffer, charCounter);
                        break;
                    case 4:
                        pNewAddressItem->zip = getStringFromBuffer(Buffer, charCounter);
                        break;
                    case 5:
                        pNewAddressItem->city = getStringFromBuffer(Buffer, charCounter);
                        break;
                    default:
                        break;
                }

                charCounter = 0;
                addressFragmentCounter++;

                // new line -> new Address
                if (c == '\n') {
                    calcHashForAddressItem(pNewAddressItem);
                    if(addressAlreadyExists(pNewAddressItem -> hash)) {
                        clearAddressItem(pNewAddressItem);
                    }
                    else {
                        addNewAddressToList(pNewAddressItem);
                        pNewAddressItem = getNewEmptyAddressItem();
                    };

                    addressFragmentCounter = 0;
                    addressCounter++;
                }
            }
        }

        fclose(fp);

        return ((addressCounter == 0) ? RET_FILE_IS_EMPTY : RET_SUCCESS);
    }
}