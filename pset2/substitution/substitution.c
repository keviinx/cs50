#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check_key_is_valid(string key); /*function for checking if key is valid */
string substitution(string plaintext, string key); /*function for substitution*/

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        /*valid amount of argument block*/
        if (check_key_is_valid(argv[1]))
        {
            /* key is valid*/
            string key = argv[1]; /*take the key as valid*/
            string plaintext = get_string("plaintext: "); /*prompt for plaintext*/
            string ciphertext = substitution(plaintext, key); /*substitute the text*/
            printf("ciphertext: %s\n", ciphertext); /*print out the substituted text*/

            return 0;
        }
        else
        {
            /* key is invalid*/
            return 1;
        }
    }
    else
    {
        /* invalid amount of argument block*/
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int check_key_is_valid(string key)
{
    string key_in_upper = key; /*key in upper same length as key*/

    if (strlen(key) != 26)
    {
        /*key not 26 char long block*/
        printf("Key must contain 26 characters.\n");
        return 0;
    }
    else
    {
        for (int i = 0; i < strlen(key); i++)
        {
            if (isdigit(key[i]))
            {
                /* key contains digit*/
                printf("Key must contain alphabetic characters.\n");
                return 0;
            }
            else
            {
                key_in_upper[i] = toupper(key[i]); /*convert all 26 char to uppercase for checking repeated characters*/
            }
        }
        for (int i = 0; i < strlen(key_in_upper); i++)
        {
            for (int j = i + 1; j < strlen(key_in_upper); j++)
            {
                if (key_in_upper[i] == key_in_upper[j])
                {
                    /* key contains repeated char*/
                    printf("Key must not contain repeated characters.\n");
                    return 0;
                }
            }
        }
        return 1;
    }
}

string substitution(string plaintext, string key)
{
    string ciphertext = plaintext; /*to get the same length*/

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if islower(plaintext[i]) /*if char is lowercaps*/
        {
            ciphertext[i] = tolower(key[((plaintext[i] - 97) %
                                         26)]); /*take the key position in array the same as plaintext position in alpha array and tolower it*/
        }
        else if isupper(plaintext[i]) /*if char is uppercase*/
        {
            ciphertext[i] = toupper(key[((plaintext[i] - 65) %
                                         26)]); /*take the key position in array the same as plaintext position in alpha array and toupper it*/
        }
        else
        {
            ciphertext[i] = plaintext[i]; /*do nothing and copy to ciphertext array*/
        }
    }

    return ciphertext;
}