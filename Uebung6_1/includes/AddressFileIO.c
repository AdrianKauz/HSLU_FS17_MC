//
// Created by Adrian Kauz on 22.04.2017.
//
#include "Address.h"
#include "AddressFileIO.h"
#include <stdio.h>

static const char SEPARATOR = '\t';

int saveAddressListToFile(struct tAddress* pAddressList){
    if(pAddressList != NULL){
        FILE *fp;
        fp = fopen("addresslist.txt", "w");

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

    return 0;
}

struct tAddress* loadAddressListFromFile(){
    return NULL;
}
