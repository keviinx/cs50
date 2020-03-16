#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height; /* height var declaration*/
    do
    {
        height = get_int("Height: "); /* ask user for height and store in height*/
    }
    while (height < 1 || height > 8); /* value has to be in between 1 and 8*/

    for (int i = 1; i <= height ; i++) /* for row control*/
    {
        for (int j = height; j > i; j--) /* this handles the differences for space printing*/
        {
            printf(" ");
        }
        for (int j = 0; j < i ; j++) /* this handles for # printing at end of spaces*/
        {
            printf("#");
        }
        printf("\n"); /* print new line*/
    }
}