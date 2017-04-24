#ifndef UEBUNG6_1_ADDRESSCONSOLEIO_H
#define UEBUNG6_1_ADDRESSCONSOLEIO_H

#define BUFFER_SIZE 50

void showMainMenue(int addressCounter);
void showAllAddresses(struct tAddress* pCurrentAddress);
struct tAddress* getNewAddressFromConsole();
char* getLine();
int isValidChar(char newChar);

#endif //UEBUNG6_1_ADDRESSCONSOLEIO_H
