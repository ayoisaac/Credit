#include <cs50.h>
#include <stdio.h>

long get_card_number(void);
int number_length(long n);
int checksum(long n);
int product_digit(long n);
int other_digit(long n);
void card_type(long number);
int starts_with(long number);

int main(void)
{
    long number = get_card_number();
    int is_card = checksum(number);

    if (is_card == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        card_type(number);
    }
}

long get_card_number(void)
{
    long number = get_long("Number: ");
    return number;
}

int checksum(long n)
{
    int sum = product_digit(n) + other_digit(n);

    if (sum % 10 == 0)
    {
        return 1;
    }
    return 0;
}

int number_length(long n)
{
    int count = 0;
    while (n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

int product_digit(long n)
{
    int length_of_n = number_length(n);
    int sum = 0;
    long mul = 10;
    int digit = 0;

    for (int i = 0; i < length_of_n / 2; i++)
    {
        digit = (n / mul) % 10;
        digit *= 2;

        if (number_length(digit) > 1)
        {
            digit = (digit % 10) +((digit / 10) % 10);
        }
        sum += digit;
        mul *= 100;
    }
    return sum;
}

int other_digit(long n)
{
    int length_of_n = number_length(n);
    int sum = n % 10;
    long mul = 100;

    for (int i = 0; i < length_of_n / 2; i++)
    {
        sum += (n / mul) % 10;
        mul *= 100;
    }
    return sum;
}

void card_type(long number)
{
    if (number_length(number) == 15 && (starts_with(number) == 34 || starts_with(number) == 37))
    {
        printf("AMEX\n");
    }

    else if (number_length(number) == 16 && (starts_with(number) == 51 || starts_with(number) == 52 || starts_with(number) == 53 || starts_with(number) == 54 || starts_with(number) == 55))
    {
        printf("MASTERCARD\n");
    }

    else if ((number_length(number) == 13 && starts_with(number) == 4) || (number_length(number) == 16 && number / 1000000000000000 == 4))
    {
        printf("here3\n");
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}

int starts_with(long number)
{
    if (number_length(number) == 16)
    {
        return number / 100000000000000;
    }
    else if (number_length(number) == 15)
    {
        return number / 10000000000000;
    }
    else if (number_length(number) == 13)
    {
        return number / 1000000000000;
    }
    return 1;
}