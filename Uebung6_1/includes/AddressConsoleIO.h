#ifndef UEBUNG6_1_ADDRESSCONSOLEIO_H
#define UEBUNG6_1_ADDRESSCONSOLEIO_H

#define USERINPUT_BUFFER_SIZE 50

void showMainMenue(int addressCounter);
struct tAddress* getNewAddressFromConsole();
char* getLine();
int isValidChar(char newChar);

#endif //UEBUNG6_1_ADDRESSCONSOLEIO_H
