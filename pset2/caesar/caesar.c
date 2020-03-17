#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int check_key_is_digit(string key); /* function for checking if key is digit*/
string caesar(string plaintext, int key); /* function for caeser the text*/

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string string_key, ciphertext; /* variable some needed strings*/
        string_key =  argv[1]; /* take the command line argument as key*/
        if (check_key_is_digit(string_key)) /*check whether key is valid*/
        {
            /* valid key block*/
            int int_key = atoi(string_key); /* convert key to int*/
            string plaintext = get_string("plaintext: "); /* obtain the string from user*/
            ciphertext = caesar(plaintext, int_key); /* caesar the text*/
            printf("ciphertext: %s\n", ciphertext); /* print the caesared text*/
        }
        else
        {
            /* invalid key block*/
            printf("Usage: ./caesar key\n");
            return 1;
        }

        return 0;
    }
    else /* argv is not a digit block*/
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

int check_key_is_digit(string key)
{
    int valid_key = 1; /* consider it valid from the beginning*/
    int key_length = strlen(key); /* take the length of the key*/

    for (int i = 0; i < key_length; i++)
    {
        if (isdigit(key[i]))
        {
            /* do nothing*/
        }
        else
        {
            valid_key = 0; /* not a valid key*/
        }
    }

    return valid_key; /* return key validity*/
}

string caesar(string plaintext, int key)
{
    string cyphertext = plaintext; /* variable for cyphertext*/

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if islower(plaintext[i]) /*if char is lowercaps*/
        {
            cyphertext[i] = ((((plaintext[i] + key) - 97) % 26) + 97); /* lowercaps a start at 97*/
        }
        else if isupper(plaintext[i]) /*if char is uppercase*/
        {
            cyphertext[i] = ((((plaintext[i] + key) - 65) % 26) + 65); /* uppercase starts at 65*/
        }
        else
        {
            cyphertext[i] = plaintext[i]; /*do nothing and copy to cyphertext array*/
        }
    }

    return cyphertext; /* return the cyphered text*/
}