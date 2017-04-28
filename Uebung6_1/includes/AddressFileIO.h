//
// Created by Adrian Kauz on 22.04.2017.
//

#ifndef UEBUNG6_1_ADDRESSFILEIO_H
#define UEBUNG6_1_ADDRESSFILEIO_H

/**
 * Sort the address list by category.
 *
 * @author  Adrian Kauz
 * @param   Current address list
 * @return  Returncode RET_SUCCESS, RET_FILE_NOT_CREATED or RET_ADDRESSLIST_IS_EMPTY
 */
eReturnCode_t exportToCSV(struct tAddress* pAddressList);


/**
 * Sort the address list by category.
 *
 * @author  Adrian Kauz
 * @return  Returncode RET_FILE_IS_EMPTY, RET_SUCCESS or RET_FILE_NOT_FOUND
 */
eReturnCode_t importFromCSV(void);

#endif //UEBUNG6_1_ADDRESSFILEIO_H
