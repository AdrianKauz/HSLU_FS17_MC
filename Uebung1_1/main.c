#include <stdio.h>

/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 1.1
 * This small program returns the degree in °Celsius for every 15°F step in Fahrenheit between 0°F and 210°F.
 *
 * @author Adrian Kauz
 * @version 1.0
 * @return 0
 */

int main() {
    printf("\nReturns the degree in celsius from a given list of values in fahrenheit\n");
    printf("***********************************************************************\n");
    printf("Fahrenheit\tCelsius\n");
    printf("----------\t-------\n");

    float degreeCelsius = 0;
    int x = 0;

    for(x; x <= 210; x = x + 15)
    {
        degreeCelsius = (5.0f/9.0f) * ((float)x - 32.0f);
        printf("%i\t\t%.3f\n", x, degreeCelsius);
    }
    printf("***********************************************************************\n");

    return 0;
}