#include <stdio.h>

/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 1.2
 * Get the greatest common divisor between two numbers.
 * If I have time it would be a good idea to check the character if it's a number or not.
 *
 * @author Adrian Kauz
 * @version 1.0
 * @date 2017.03.14
 * @return 0
 */

double getGGT(double firstNumber, double secondNumber);


int main() {
    printf("\nGet the greatest common divisor\n");
    printf("*********************************\n");

    double firstNumber = 0;
    double secondNumber = 0;

    printf("First Number: ");
    scanf("%d", &firstNumber);
    printf("Second Number: ");
    scanf("%d", &secondNumber);


    printf("The greatest common divisor is: %d", getGGT(firstNumber, secondNumber));

    return 0;
}


double getGGT(double firstNumber, double secondNumber)
{
    if(firstNumber == 0)
    {
        return secondNumber;
    }
    else
    {
        while (secondNumber != 0)
        {
            if(firstNumber > secondNumber)
            {
                firstNumber -= secondNumber;
            }
            else
            {
                secondNumber -= firstNumber;
            }
        }

        return firstNumber;
    }
}