#include <cs50.h>
#include <stdio.h>
#include <math.h>
//Acquires initial population value from user

//Acquires target population value from user

//Calculates number of years it will take for inital to reach target

//Prints number of years to user




int main(void)
{
    //Acquires starting population
    
    int pstart;
    do
    {
        pstart = get_int("What is the starting population? \n");
    }
    while (pstart < 9);
    //Acquires target population
    
    int pend;
    do
    {
        pend = get_int("What is the target population? \n");
    }
    while (pend < pstart);
    
    //This variable will count the amount of years elapsed
    int years = 0;

    while (pstart < pend)
    
    {
        pstart = trunc(pstart + (pstart / 3) - (pstart / 4));
        years++;
    }
    //Prints result
    printf("Years: %i\n", years);
}
