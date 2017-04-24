//
// Created by Adrian Kauz on 22.04.2017.
//

#ifndef UEBUNG6_1_ADDRESSFILEIO_H
#define UEBUNG6_1_ADDRESSFILEIO_H

int exportToFile(struct tAddress* pAddressList);
struct tAddress* importFromFile();
char* getStringFromBuffer(char* buffer, int len);

#endif //UEBUNG6_1_ADDRESSFILEIO_H
