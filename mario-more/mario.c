#include <cs50.h>
#include <stdio.h>

int height();
void builder(int size);

int main(void)
{
    int h = height();
    builder(h);
}


//function acquires desired build height
int height()
{
    int x;
    do
    {
        x = get_int("Height: ");
    }
    while (x < 1 || x > 8);
    return x;
}
//function builds pyramid
void builder(int size)
{
    //declaring prototype values for later use
    int space = 0;
    int width = 1;
    int blocks = 0;
    //executes builder until desired height
    do
    {
        //prints spaces for pyramid
        for (space = 0; space < size - width; space++)
        {
            printf(" ");
        }

        //left side build
        for (blocks = 0; blocks < width; blocks++)

        {
            printf("#");
        }

        //adds gap
        printf("  ");

        //right side build
        for (blocks = 0; blocks < width; blocks++)
        {
            printf("#");
        }
        printf("\n");
        width++;
    }
    while (width <= size);
}