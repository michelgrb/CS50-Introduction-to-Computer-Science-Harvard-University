// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// Number of bytes in .wav header
const int HEADER_SIZE = 44;

//typedef uint8_t head[HEADER_SIZE];
//typedef int16_t buffer;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
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

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    // TODO: Copy header from input file to output file

    //header for c (44)
    uint8_t head[HEADER_SIZE];

    //copy first 44 Bytes
    fread(&head, sizeof(head), 1, input);
    fwrite(&head, sizeof(head), 1, output);


    // TODO: Read samples from input file and write updated data to output file

    //short datatyp for buffer
    int16_t buffer;

    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        // set buffer to factor
        buffer = buffer * factor;

        // write new buffer into "new" file
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
    return 0;
}
