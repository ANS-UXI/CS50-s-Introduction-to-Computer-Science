#include <cs50.h>
#include <stdio.h>

int length(long num);
int checksum(long num);

int main(void)
{
    long num = get_long("Number: ");
    int flag_1 = checksum(num);
    int len = length(num);
    int First_digit = 0, flag_2 = 0;
    string type;
    long r = 0, x = 0;
    switch (len) // Switch case for selecting card type on the basis of length
    {
        case 15:
            while (num != 0)
            {
                int d = num % 10;
                r = r * 10 + d; // Reversing the number
                num /= 10;
            }
            if (r % 100 == 43 || r % 100 == 73) // Actual prefix numbers are 34 & 37 for American Express
            {
                type = "AMEX";
                flag_2 = 1;
            }
            break;

        case 13:
            type = "VISA";
            flag_2 = 1;
            break;

        case 16:
            x = num; // Taking a copy of the orginal value
            while (num != 0)
            {
                First_digit = num % 10;
                num /= 10;
            }
            if (First_digit == 4)
            {
                type = "VISA";
                flag_2 = 1;
            }
            else if (First_digit == 5)
            {
                while (x != 0)
                {
                    int d = x % 10;
                    r = r * 10 + d; // Reversing the number
                    x /= 10;
                }
                for (int i = 5; i <= 55 ; i += 10) // Loop for comparing prefixes between 50-55 for Mastercard
                {
                    if (r % 100 == i)
                    {
                        type = "MASTERCARD";
                        flag_2 = 1;
                    }
                }
            }
            else
            {
                type = "INVALID";
            }
            break;

        default:
            type = "INAVLID";
            break;
    }
    if (flag_1 == 1 && flag_2 == 1) // Comparing if both criteria satisfies
    {
        printf("%s\n", type);
    }
    else
    {
        printf("INVALID\n");
    }
}

int length(long num) // Returns the length of a long type value
{
    int sum = 0;
    while (num != 0)
    {
        sum++;
        num /= 10;
    }
    return sum;
}

int checksum(long num) // Returns whether a card number is valid or not by using 0/1 (Luhn’s Algorithm)
{
    int flag = 1, sum_1 = 0, sum_2 = 0;
    while (num != 0)
    {
        if (flag == 1)
        {
            int digit = num % 10; // Extracting digits
            sum_1 += digit; // Sum of extracted digits
            flag = 0;
        }
        else
        {
            int digit = num % 10;
            int x = digit * 2;
            if (x <= 9)
            {
                sum_2 += x; // Adding product digits of a single digit number
            }
            else
            {
                while (x != 0)
                {
                    int d = x % 10;
                    sum_2 += d; // Adding product digits of a double digit number
                    x /= 10;
                }
            }
            flag = 1;
        }
        num /= 10;
    }
    if (((sum_1 + sum_2) % 10) == 0) // Checking whether their sum's last digit is 0
    {
        return 1;
    }
    return 0;
}