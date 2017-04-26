#ifndef UEBUNG6_1_ADDRESSCONSOLEIO_H
#define UEBUNG6_1_ADDRESSCONSOLEIO_H

#define BUFFER_SIZE 50

struct eReturnCode_t;

void showMainMenue(int addressCounter);
void startAddressManager();
struct tAddress* getNewAddressFromConsole();
char* getLine();
int isValidChar(char newChar);
void showAllAddresses(struct tAddress*);
void showPressEnterToContinue(void);

#endif //UEBUNG6_1_ADDRESSCONSOLEIO_H
