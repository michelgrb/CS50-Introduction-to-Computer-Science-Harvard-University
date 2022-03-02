// a program that recovers JPEGs from a forensic image

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>

struct stat st;
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    stat(argv[1], &st);
    int size = st.st_size;
    FILE *output = NULL;
    BYTE buffer[512];
    int count = 0;
    int term = 0;

    //max size for outp (not used)
    int maxim = size / sizeof(buffer);

    while (fread(buffer, sizeof(buffer), 1, input) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // is term 1??
            if (term == 1)
            {
                //close open file
                fclose(output);
            }
            else
            {
                term = 1;
            }


            char name[8];

            //create outputname
            sprintf(name, "%03d.jpg", count);
            output = fopen(name, "w");
            count++;

        }

        if (term == 1)
        {
            //write output if term == 1
            fwrite(buffer, sizeof(buffer), 1, output);
        }


    }

    fclose(input);

    return 0;

}

