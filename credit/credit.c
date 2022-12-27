#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
//prototypes all the functions
long ask();
int iscard(long card);
int checksum(long card);
void brand(long card);

int main(void)
{
    long num = ask();
    //checks if given number is a card, if not exit
    if (iscard(num) == 0)
    {
        return 0;
    }
    //performs Luhn Algorithm check
    if (checksum(num) == 0)
    {
        return 0;
    }
    //identifies and returns the brand
    brand(num);

}


long ask()
{
    //acquires numbers only
    return get_long("Insert card: ");
}

int iscard(long card)
{
    //determines lenght of number
    int len = 0;
    long cc = card;
    //runs the loop until no digits
    //counts primitively by adding 1 for
    //every loop instance
    while (cc > 0)
    {

        cc = cc / 10;
        len++;
    }
    //checks if the lenght is different than below
    //and exits with INVALID
    if (len != 15 && len != 13 && len != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    else;
    {
        return 1;
    }
}

int checksum(long card)
{
    //check1 & 2 will do the sum
    int check1 = 0;
    int check2 = 0;
    //total will serve to add 1 & 2 for modulus
    int total = 0;
    //last will acquire the last digits using modulus
    int last1;
    int last2;
    //div will be used for check2 for Luhn
    int div1;
    int div2;
    //ye is arbitrary as our card operating number
    long ye = card;

    do
    {
        //this will acquire the last digit
        last1 = ye % 10;
        //this will remove the last digit, previously acquired
        ye = ye / 10;
        //now we add the last digit to the first check
        check1 = check1 + last1;

        //this will acquire the next last digit
        last2 = ye % 10;
        //once again removing the last digit
        ye = ye / 10;


        //as we have an acquirer
        //we now multiply or add according to Luhn
        //last2 is multiplied, as they are the second digits
        //div1 and 2 will individualize the digits
        last2 = last2 * 2;
        div1 = last2 % 10;
        div2 = last2 / 10;
        //now add the individual digits to the check2 sum
        check2 = check2 + div1 + div2;

    }
    //loop will continue until ye is 0,
    //meaning we acquire and remove all digits.
    while (ye > 0);

    //total adds our sums and then modulus for remainder.
    total = check1 + check2;
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    return 1;

}
//will acquire first digits and select appropriate brand
void brand(long card)
{
    long long num = card;
    //this will run the loop until we have
    //double digits
    while (num >= 100)
    {
        //divides number by 10
        //effectively removing last digit
        num /= 10;
    }
    //now that it's double digit
    //removes last and checks if VISA
    if (num / 10 == 4)
    {
        printf("VISA\n");
    }
    //checks if dd is MASTERCARD
    else if (num >= 51 && num <= 55)
    {
        printf("MASTERCARD\n");
    }
    //checks if AMEX
    else if (num == 34 || num == 37)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
