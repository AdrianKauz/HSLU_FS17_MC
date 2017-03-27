/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 2.2
 * Convert a integer value to a string
 * Because the int-Type is a 32-Bit signed integer the allowed range is:
 * 0 <-> 2147483647
 * @author Adrian Kauz
 * @version 1.0
 * @date 2017.03.27
 * @return 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char* intToString(int newInt, char* newString);

int main() {
    system("cls");

    char* string = intToString(2147483647, string);

    printf("Resultat: %s", string);

    return(EXIT_SUCCESS);
}

/**
 * Convert a 32bit integer to a string
 * @author Adrian Kauz
 * @param Integervalue to convert, char-pointer
 * @return converted integer
 */
char* intToString(int newInt, char* pNewString){
    int letterCount = newInt == 0 ? 1 : (int) ceil(log10(newInt));

    // Check for 1, 10, 100, 1000...
    if( newInt == pow(10, letterCount)){
        letterCount++;
    }

    // Reserve space
    pNewString = (char*) malloc(sizeof(char) * (letterCount + 1)); // One more for the "\0"

    // Convert int to string
    int x = letterCount, temp, currentInt = newInt;
    for(x ; 0 < x ; x--){
        temp = pow(10, x - 1);
        *(pNewString + letterCount - x) = (char) (48 + (currentInt / temp));
        currentInt -= temp * (currentInt / temp);
    }


    *(pNewString + letterCount) = '\0';

    return pNewString;
}