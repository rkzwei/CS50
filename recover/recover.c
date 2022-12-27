#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    unsigned char block[512];
    //limit arg count to 1
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    //open file and check if valid
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Invalid file\n");
        return 2;
    }
    // prototypes output file
    FILE *output = NULL;
    // keeps track of images generated
    int counter = 0;
    // frees memory so we can use
    char *fname = malloc(8 * sizeof(char));

    // read
    while (fread(block, sizeof(char), 512, input))
    {
        // check for signature
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // closes output file so a new cycle can begin
            if (counter > 0)
            {
                fclose(output);
            }
            // correctly names files
            sprintf(fname, "%03i.jpg", counter);
            output = fopen(fname, "w");
            // adds to counter so that files can be named appropriately
            counter++;
        }
        // checks if the file is empty so that it can be written to
        if (output != NULL)
        {
            fwrite(block, sizeof(char), 512, output);
        }
    }
    //frees memory and closes junk
    free(fname);
    fclose(output);
    fclose(input);

    return 0;
}