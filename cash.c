#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars = 0;

    //ask for owed dollars
    do
    {
        dollars = get_float("Change owed:");
    }
    while (dollars <= 0);

    //determinate errors (round)
    int rg = round(dollars * 100);
    //printf("%i\n",rg);

    //count for coins
    int x = 0;

    //start proofing how many coins need
    while ((rg - 25) >= 0)
    {
        rg = rg - 25;
        x = x + 1;
        //printf("0.25$:%i\n",rg);
    }

    while ((rg - 10) >= 0)
    {
        rg = rg - 10;
        x = x + 1;
        //printf("0.10$:%i\n",rg);
    }

    while ((rg - 5) >= 0)
    {
        rg = rg - 5;
        x = x + 1;
        //printf("0.05$:%i\n",rg);
    }

    while ((rg - 1) >= 0)
    {
        rg = rg - 1;
        x = x + 1;
        //printf("0.01$:%i\n",rg);
    }

    printf("%i\n", x);
}
