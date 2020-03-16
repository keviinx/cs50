#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int coins = 0; /* declare var for coins to return*/
    int change_in_cents = 0; /* declare var for change in cents*/
    float change; /* declare change variable*/

    do
    {
        change = get_float("Change owed: "); /* ask for amount of change owed*/
    }
    while (change < 0);
    
    change_in_cents = round(change * 100); /* convert to cents */
    coins += change_in_cents / 25; /* divide by quarters*/
    change_in_cents = change_in_cents % 25; /* leftover change from quarters*/
    coins += change_in_cents / 10; /* divide by dimes*/
    change_in_cents = change_in_cents % 10; /* leftover change from dimes*/
    coins += change_in_cents / 5; /* divide by nickels*/
    change_in_cents = change_in_cents % 5; /* leftover change from nickels*/
    coins += change_in_cents / 1; /* divide by pennies*/

    printf("%i\n", coins);

}