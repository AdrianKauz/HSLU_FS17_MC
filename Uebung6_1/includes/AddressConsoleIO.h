#ifndef UEBUNG6_1_ADDRESSCONSOLEIO_H
#define UEBUNG6_1_ADDRESSCONSOLEIO_H

/**
 * Shows the main menu.
 *
 * @author  Adrian Kauz
 * @param   Number of addresses as integer.
 */
void showMainMenue(int);


/**
 * The main loop of the address manager.
 *
 * @author  Adrian Kauz
 */
void startAddressManager(void);


/**
 * Shows a mask to enter a new address.
 *
 * @author  Adrian Kauz
 * @return  A new address item.
 */
struct tAddress* getNewAddressFromConsole(void);


/**
 * Reads a new string from the console.
 *
 * @author  Adrian Kauz
 * @return  A new allocated string from getStringFromBuffer()
 */
char* getString(void);


/**
 * Reads a new number from the console as unsigned integer.
 *
 * @author  Adrian Kauz
 * @return  An unsigned Integer. Function is not save, because there's no check
 *          if input is a number or an alpha!
 */
unsigned int getNumberFromConsole(void);


/**
 * My own check for valid chars. TRUE or FALSE should returned as
 * type eBoolean_t. But somehow the compiler whines around...
 *
 * @author  Adrian Kauz
 * @return  TRUE or FALSE
 */
int isValidChar(char);


/**
 * Shows all current loaded addresses.
 *
 * @author  Adrian Kauz
 * @param  Current address list
 */
void showAllAddresses(struct tAddress*);


/**
 * Shows "Press <Enter> to continue..." and handles
 * the ENTER-Input with fflush().
 *
 * @author  Adrian Kauz
 */
void showPressEnterToContinue(void);

#endif //UEBUNG6_1_ADDRESSCONSOLEIO_H
