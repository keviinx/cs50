#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) /*if argument count is not 2*/
    {
        printf("Usage: ./recover image\n"); /*print error message*/
        return 1;
    }

    char *filename = argv[1]; /*take the input file name*/
    FILE *f = fopen(filename, "r"); /*open the file*/

    BYTE buffer[BLOCK_SIZE]; /*make buffer of block size*/
    int image_number = 0; /*image counter to 0*/

    char file_name[8]; /*length of filename is 8 000.jpg\0*/
    FILE *o = NULL; /*output file pointer to null*/

    while (fread(buffer, BLOCK_SIZE, 1, f) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (image_number > 0) /*if image already created*/
            {
                fclose(o); /*close the file*/
            }

            sprintf(filename, "%03i.jpg", image_number); /*print the name of the file*/

            o = fopen(filename, "w"); /*open the file*/

            image_number++; /*increment the number*/
        }

        if (o != NULL) /*if the image is not null*/
        {
            fwrite(buffer, BLOCK_SIZE, 1, o); /*write the image*/
        }
    }

    fclose(o); /*close for last image*/

    fclose(f); /* close input file*/

    return 0;
}
