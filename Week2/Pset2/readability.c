#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string inp = get_string("Text:");
    int len = strlen(inp);

    //printf("%i", len);

    // splitter
    string space = " ";
    string ends = ".!?,'";

    //count words

    int words = 1;

    for (int i = 0; i < len; i++)
    {
        if (inp[i] == space[0])
        {
            words++;
        }
    }

    //count letters
    int letter = 0;

    for (int i = 0; i < len; i++)
    {
        inp[i] = toupper(inp[i]);
        //what is not a letter
        if (inp[i] >= 'A' && inp[i] <= 'Z')
        {
            letter++;
        }
    }

    //count sentences

    int sentence = 0;

    for (int i = 0; i < len; i++)
    {
        if (inp[i] == ends[0] || inp[i] == ends[1] || inp[i] == ends[2])
        {
            sentence++;
        }
    }

    float s = (float)sentence / words * 100;
    float l = (float)letter / words * 100;

    //printf("l:%f\ns:%f\n", l, s);

    //create grade
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    if (index < 16 && index > 0)
    {
        printf("Grade %i\n", index);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
    //printf("Words:%i\nLetter:%i\nSentence:%i\n", words, letter, sentence);
}
