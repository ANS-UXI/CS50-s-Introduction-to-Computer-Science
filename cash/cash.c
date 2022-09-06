#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int flag = 1, ncents; // Flag varibale to check whether lies between 1-99
    do
    {
        ncents = get_int("Enter the number of cents: "); // Prompting user to enter no. of cents
        if (ncents >= 0)
        {
            flag = 0;
        }
    }
    while (flag != 0);
    return ncents;
}

int calculate_quarters(int cents)
{
    if (cents >= 25) // Checking whether no. of cents are above par
    {
        int x = cents, counter = 0;
        while (x >= 25)
        {
            counter++;
            x -= 25;
        }
        return counter;
    }
    return 0;
}

int calculate_dimes(int cents)
{
    if (cents >= 10) // Checking whether no. of cents are above par
    {
        int x = cents, counter = 0;
        while (x >= 10)
        {
            counter++;
            x -= 10;
        }
        return counter;
    }
    return 0;
}

int calculate_nickels(int cents)
{
    if (cents >= 5) // Checking whether no. of cents are above par
    {
        int x = cents, counter = 0;
        while (x >= 5)
        {
            counter++;
            x -= 5;
        }
        return counter;
    }
    return 0;
}

int calculate_pennies(int cents)
{
    if (cents >= 1) // Checking whether no. of cents are above par
    {
        int x = cents, counter = 0;
        while (x >= 1)
        {
            counter++;
            x -= 1;
        }
        return counter;
    }
    return 0;
}