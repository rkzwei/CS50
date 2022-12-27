#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? \n");
    // acquires user's name;
    printf("hello, %s\n", name);
    // prints hello followed by user's name;
}
