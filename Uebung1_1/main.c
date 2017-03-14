#include <stdio.h>

/**
 * This small program returns the degree in °Celsius for every 15°F step in Fahrenheit between 0°F and 210°F.
 *
 * @author Adrian Kauz
 * @version 1.0
 * @return 0
 */

int main() {
    printf("Ausgabe von C Temperaturen aus einer Reihe von Fahrenheit-Werten\n");
    printf("----------------------------------------------------------------\n");

    float degreeCelsius = 0;
    int x = 0;

    for(x; x <= 210; x = x + 15)
    {
        degreeCelsius = (5.0f/9.0f) * ((float)x - 32.0f);
        printf("%i\t%f\n", x, degreeCelsius);
    }
    printf("----------------------------------------------------------------\n");

    return 0;
}