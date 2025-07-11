#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // CHECKING COMMAND LINE ARGUMENTS
    if (argc != 2)
    {
        printf("Usage: ./recover [jpeg file name]\n");
        return 1;
    }

    // OPENING FILE
    FILE *inptr = fopen(argv[1], "r");

    // CHECKING FOR FILE OPENING ISSUES
    if (inptr == NULL)
    {
        printf("Could not open the file\n");
        return 1;
    }

    // Array or block of one byte (8 bit) data
    uint8_t buffer[512];
    FILE *newjpeg = NULL;
    int count = 0;
    char *name = malloc(8 * sizeof(char)); // 8 because X+X+X+.+j+p+e+g=8

    if (name == NULL)
    {
        printf("Memory not allocated\n");
        fclose(inptr); // Ensure the file is closed before exiting
        return 1;
    }

    while (fread(buffer, sizeof(BYTE), 512, inptr) == 512)
    {
        // Check for the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If already writing a JPEG, close it
            if (newjpeg != NULL)
            {
                fclose(newjpeg);
            }

            // Create a new file for the new JPEG
            sprintf(name, "%03i.jpg", count);
            newjpeg = fopen(name, "w");

            if (newjpeg == NULL)
            {
                free(name);
                fclose(inptr);
                printf("File creation error\n");
                return 1;
            }
            count++;
        }

        // If a JPEG file is open, write the buffer to it
        if (newjpeg != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, newjpeg);
        }
    }

    // Close any remaining open files and free memory
    if (newjpeg != NULL)
    {
        fclose(newjpeg);
    }
    fclose(inptr);
    free(name);
    return 0;
}
