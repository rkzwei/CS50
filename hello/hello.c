#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("What's your name? \n");
    //receives user name
    printf("hello, %s\n", answer);
    //prints hello followed by inputted answer
}