#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name?\n"); /* ask for name and store in name var*/
    printf("hello, %s\n", name); /* print out hello, name var*/
}