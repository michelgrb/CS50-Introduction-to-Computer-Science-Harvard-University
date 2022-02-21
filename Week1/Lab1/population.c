// Determine how long it takes for a population to reach a particular size.

#include<stdio.h>
#include<cs50.h>

int main(void)
{

    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for start size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int years;
    int count;

    count = start;
    years = 0;

    while (count < end)
    {
        count = count + (count / 3) - (count / 4);
        years = years + 1;
    }


    // TODO: Print number of years

    printf("Years: %i", years);

}
