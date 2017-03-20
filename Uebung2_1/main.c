/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 2.1
 * Change the direction of a given set of characters and give it out on the console.
 * Get the characters via console (user inputs or simple file stream)
 *
 * @author Adrian Kauz
 * @version 1.0
 * @date 2017.03.20
 * @return 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** Function declaration */
char* readString(char* text);
char* reverse(char* character);


/** Main */
int main(int argc, char* argv[])
{
    system("cls");
    printf("Bitte Text eingeben --> ");
    char* text = readString(text);
    system("cls");
    printf("Eingegebener Text --> \t%s", text);
    printf("\n\n--------------------------------------------------\n\n");
    printf("Verarbeiteter Text --> \t%s\n", reverse(text));

    return(EXIT_SUCCESS);
}

/**
 * Reads input-stream from console. Memory is dynamically allocated.
 * @author Adrian Kauz
 * @param Empty Pointer
 * @return Pointer with all the characters from console
 */
char* readString(char* pText)
{
    int i = 0;
    char c;
    int blockSize = 10;

    //Initial the first memoryblock
    pText = (char *) malloc(sizeof(char) * blockSize);

    if(pText)
    {
        while ((c = getchar()) != EOF && c != '\n')
        {
            *(pText + i) = c;
            i++;

            if(i % 10 == 0)
            {
                //Extend current memory with another block
                pText = (char *) realloc(pText, sizeof(char) * (i + blockSize));

                if (!pText)
                {
                    return pText;
                }
            }
        }

        *(pText + i) = '\0';
    }

    return pText;
}

/**
 * Change order of characters in a array
 * From: "paxdiablo" --> http://stackoverflow.com/a/784567
 * Simple but effective.
 * @author Adrian Kauz
 * @param Text to reverse
 * @return Reversed text
 */
char* reverse(char* pString)
{
    if(pString != NULL)
    {
        size_t len = strlen(pString);

        if(len > 1)
        {
            char temp, *pSrc, *pDst;

            pSrc = pString;
            pDst = pString + len - 1;

            while(pSrc < pDst)
            {
                temp = *pSrc;
                *pSrc++ = *pDst;
                *pDst-- = temp;
            }
        }
    }

    return pString;
}