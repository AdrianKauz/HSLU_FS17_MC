#ifndef UEBUNG6_1_ADDRESSCONSOLEIO_H
#define UEBUNG6_1_ADDRESSCONSOLEIO_H

struct eReturnCode_t;

void showMainMenue(int);
void startAddressManager(void);
struct tAddress* getNewAddressFromConsole(void);
char* getLine(void);
int isValidChar(char);
void showAllAddresses(struct tAddress*);
void showPressEnterToContinue(void);

#endif //UEBUNG6_1_ADDRESSCONSOLEIO_H
