#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 1.4
 * Write a little menue with the selection A, B, C, Q
 *
 * @author Adrian Kauz
 * @version 1.0
 * @date 2017.03.17
 * @return 0
 */

void drawMenue();
void doSomethingA();
void doSomethingB();
void doSomethingC();

int main(int argc,char *argv[])
{
    char pressedKey;

    do
    {
        drawMenue();

        printf("Enter Selection: ");
        pressedKey = toupper(getchar());
        fflush(stdin);

        switch(pressedKey)
        {
            case 'A':
                    doSomethingA();
                    getchar();
                break;
            case 'B':
                    doSomethingB();
                    getchar();
                break;
            case 'C':
                    doSomethingC();
                    getchar();
                break;
            case 'Q':
                    system("cls");
                    printf("Goodbye!\n");
                break;
            default:
                    printf("\nInvalid Option!");
                    getchar();
                break;
        }
    }
    while(pressedKey != 'Q');

    return(EXIT_SUCCESS);
}

void drawMenue()
{
    system("cls");

    printf("*******************************************************************************\n");
    printf(" A simple menue (Press key for Option)\n");
    printf("*******************************************************************************\n");
    printf("\n");
    printf("(A) --> Select program A\n\n");
    printf("(B) --> Select program B\n\n");
    printf("(C) --> Select program C\n\n");
    printf("(Q) --> Exit\n\n");
    printf("*******************************************************************************\n\n");

    return;
}

void doSomethingA()
{
    printf("\nMenue A was choosen by the user!");
    return;
}

void doSomethingB()
{
    printf("\nMenue B was choosen by the user!");
    return;
}

void doSomethingC()
{
    printf("\nMenue C was choosen by the user!");
    return;
}
