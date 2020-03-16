#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit_card_number; /* variable for credit card number*/
    long credit_card_number_for_process; /* variable for credit card for processing*/
    int credit_card_number_length = 0; /*variable for card number length*/
    int digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9, digit_10, digit_11, digit_12, digit_13,
        digit_14, digit_15, digit_16; /* variable for all the digits*/
    int checksum; /* variable for checksum*/
    int mastercard_check; /* variable for checking mastercard*/
    int amex_check; /* variable for checking amex*/

    do
    {
        credit_card_number = get_long("Number: "); /* prompt the user for number*/
    }
    while (credit_card_number < 0);

    credit_card_number_for_process = credit_card_number; /* replicate the card number for processing*/

    do
    {
        credit_card_number_for_process = credit_card_number_for_process / 10; /*divide by 10 to get length*/
        credit_card_number_length++; /*increase the length*/
    }
    while (credit_card_number_for_process != 0); /* repeat until 0*/

    if (credit_card_number_length != 13 && credit_card_number_length != 15 && credit_card_number_length != 16)
    {
        printf("INVALID\n"); /*invalid card length*/
    }
    else /*valid card length block*/
    {
        /* splitting digits block*/
        digit_1 = credit_card_number % 10;
        digit_2 = ((credit_card_number % 100) / 10) * 2; /* every second number must multiply by 2*/
        digit_3 = (credit_card_number % 1000) / 100;
        digit_4 = ((credit_card_number % 10000) / 1000) * 2;
        digit_5 = (credit_card_number % 100000) / 10000;
        digit_6 = ((credit_card_number % 1000000) / 100000) * 2;
        digit_7 = (credit_card_number % 10000000) / 1000000;
        digit_8 = ((credit_card_number % 100000000) / 10000000) * 2;
        digit_9 = (credit_card_number % 1000000000) / 100000000;
        digit_10 = ((credit_card_number % 10000000000) / 1000000000) * 2;
        digit_11 = (credit_card_number % 100000000000) / 10000000000;
        digit_12 = ((credit_card_number % 1000000000000) / 100000000000) * 2;
        digit_13 = (credit_card_number % 10000000000000) / 1000000000000;
        digit_14 = ((credit_card_number % 100000000000000) / 10000000000000) * 2;
        digit_15 = (credit_card_number % 1000000000000000) / 100000000000000;
        digit_16 = ((credit_card_number % 10000000000000000) / 1000000000000000) * 2;

        /* checksum block*/
        checksum = (digit_1 % 10) + ((digit_1 % 100) / 10);
        checksum += (digit_2 % 10) + ((digit_2 % 100) / 10);
        checksum += (digit_3 % 10) + ((digit_3 % 100) / 10);
        checksum += (digit_4 % 10) + ((digit_4 % 100) / 10);
        checksum += (digit_5 % 10) + ((digit_5 % 100) / 10);
        checksum += (digit_6 % 10) + ((digit_6 % 100) / 10);
        checksum += (digit_7 % 10) + ((digit_7 % 100) / 10);
        checksum += (digit_8 % 10) + ((digit_8 % 100) / 10);
        checksum += (digit_9 % 10) + ((digit_9 % 100) / 10);
        checksum += (digit_10 % 10) + ((digit_10 % 100) / 10);
        checksum += (digit_11 % 10) + ((digit_11 % 100) / 10);
        checksum += (digit_12 % 10) + ((digit_12 % 100) / 10);
        checksum += (digit_13 % 10) + ((digit_13 % 100) / 10);
        checksum += (digit_14 % 10) + ((digit_14 % 100) / 10);
        checksum += (digit_15 % 10) + ((digit_15 % 100) / 10);
        checksum += (digit_16 % 10) + ((digit_16 % 100) / 10);

        if (checksum % 10 != 0)
        {
            printf("INVALID\n"); /* invalid checksum*/
        }
        else
        {
            /* Check card by length*/
            if (credit_card_number_length == 16)
            {
                if (digit_16 / 2 == 4)
                {
                    printf("VISA\n"); /* valid VISA card*/
                }
                else
                {
                    mastercard_check = credit_card_number / 100000000000000;
                    if (mastercard_check == 51 || mastercard_check == 52 || mastercard_check == 53 || mastercard_check == 54 || mastercard_check == 55)
                    {
                        printf("MASTERCARD\n"); /* valid mastercard*/
                    }
                    else
                    {
                        printf("INVALID\n"); /* invalid mastercard*/
                    }
                }
            }
            else if (credit_card_number_length == 15)
            {
                amex_check = credit_card_number / 10000000000000;
                if (amex_check == 34 || amex_check == 37)
                {
                    printf("AMEX\n"); /* valid american express*/
                }
                else
                {
                    printf("INVALID\n"); /* invalid american express*/
                }
            }
            /*13 length check block*/
            else 
            {
                if (digit_13 == 4)
                {
                    printf("VISA\n"); /* valid VISA card*/
                }
                else
                {
                    printf("INVALID\n"); /* invalid VISA card*/
                }
            }
        }
    }    

}