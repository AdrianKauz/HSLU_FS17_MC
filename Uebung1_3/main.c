#include <stdio.h>
#include <math.h>

/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 1.3
 * Convert a 32bit signed integer to binary, represented in ascii.
 * Example: "45'623'131" -> "‭0010'1011'1000'0010'0111'0101'1011‬"
 * Code is not perfect, but it works. User is still able to enter invalid values!
 *
 * @author Adrian Kauz
 * @version 1.0
 * @date 2017.03.15
 * @return 0
 */

int main(int argc,char *argv[])
{
    printf("\nGet the binary representation of an 32bit signed Integer\n");
    printf("**************************************************\n");

    int number = 0;

    printf("Please enter a valid 32bit-integer value: ");
    scanf("%i", &number);
    fflush(stdin);

    int binarySizeOfNumber = sizeof(number) * 8;
    int mask = pow(2,binarySizeOfNumber - 2); // Start with the left side after MSB-Bit

    printf("\nbinarySizeOfNumber is: %i", binarySizeOfNumber);
    printf("\nBinary value of %i is: ", number);

    // Value is negative?
    (number < 0) ? printf("1") : printf("0");

    int counter = binarySizeOfNumber - 1; // MSB-Bit doesn't count.
    for(counter; counter > 0; counter--)
    {
        ((number & mask) > 0) ? printf("1") : printf("0");

        // Eyecandy
        if((counter > 1) && (counter % 4) == 1)
        {
            printf("'");
        }

        mask = mask >> 1;
    }

    printf("\n**************************************************\n");

    return 0;
}
