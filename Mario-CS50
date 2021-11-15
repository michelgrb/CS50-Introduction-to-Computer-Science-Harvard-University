#include <stdio.h>
#include <cs50.h>

int main(void)
{

    //ask user for inp
    int n;

    do
    {
        n = get_int("Height:");
    }
    while ((n < 1) || (n > 8));

    //declare variable
    int x = 1;
    int i = n;

    // start loop for layers
    for (x = 1; x <= n; x++)
    {
        int z = 1;
        int y = 0;

        // print space for steps of pyramide
        for (z = 1; z < i; z++)
        {
            printf(" ");
        }

        //print "#" for pyramide
        for (y = 0; y < x; y++)
        {
            printf("#");
        }

        //i-- because of less space " "
        i--;

        //set used vaiable to start value
        z = 1;
        y = 0;

        printf("\n");
    }

}
