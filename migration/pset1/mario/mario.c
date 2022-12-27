#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Defines variables for later use
    int width = 1;
    int block = 0;
    int space = 0;
    
    //Acquires user input for pyramid height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    //Executes the pyramid code until width matches the height
    do
    {
        //Executes print function for space until it hits the required amount
        for (space = 0; space < height - width; space++)
        {
            printf(" ");
        }
        //Prints left side of the pyramid according to the height
        for (block = 0; block < width; block++)
        {
            printf("#");
        }
        
        //Adds a gap of two spaces in the middle
        printf("  ");
        
        //Prints right side of the pyramid according to the height
        for (block = 0; block < width; block++)
        {
            printf("#");
        }
        //Sends the code to the next line to continue executing and adds to the width count for proper block placement
        printf("\n");
        width++;
    }
    while (width <= height);
    
}
