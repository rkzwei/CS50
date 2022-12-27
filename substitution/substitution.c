#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int alphacheck(string u_input);
int shift(string crypt, string key);

int main(int argc, string argv[])
{
    string inputt = argv[1];
    //runs check for valid number of command line args
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //checks if alphabetic, if duplicate, if 26 chars
    else if (alphacheck(inputt) != 0)
    {
        return 1;
    }
    else
    {
        string plain = get_string("plaintext:  ");
        //performs shift by acquiring user input and the key
        shift(plain, inputt);
        printf("\n");
        return 0;
    }
}

int shift(string crypt, string key)
{
    //defines text lenght constant
    int textlen = strlen(crypt);
    //prototypes shift array
    char shiftbook[26];
    //int debugcount = 0;
    //prototypes printing array
    char printbook[textlen];
    //makes shift array to be equal to ASCII a through z
    for (int n = 0; n != 26; n++)
    {
        shiftbook[n] = 97 + n;
        //debugcount ++;
    }
    printf("ciphertext: ");
    //printf("%i %c\n", debugcount, shiftbook[25]);
    //executes shift function until full lenght
    for (int n = 0; n != textlen + 1; n++)
    {
        //checks if char is alphabetic and adds to book if not
        if (isalpha(crypt[n]) == 0)
        {
            printbook[n] = crypt[n];
        }

        for (int s = 0; s != 26; s++)
        {
            //checks if text char is lowercase, adds if so
            if (shiftbook[s] == crypt[n])
            {
                printbook[n] = (tolower(key[s]));
            }
            //checks and adds char and Uppercase it after shifting
            else if (shiftbook[s] == tolower(crypt[n]))
            {
                printbook[n] = toupper(key[s]);
            }
        }

    }
    //prints array, already ciphered
    printf("%s", printbook);
    //printf(" \n");
    return 0;
}



int alphacheck(string u_input)
{
    //checks if key is 26 char long
    if (strlen(u_input) != 26)
    {
        //printf("%s\n", key);
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char book[25];
    //iterates through 26 letters
    for (int n = 0; n != 26; n++)
    {
        book[n] = u_input[n];
        //checks for alphabet
        if (isalpha(u_input[n]) == 0)
        {
            printf("Invalid key: Key contains non-alphabetical char.\n");
            return 2;
        }
        //checks if duplicate
        for (int s = 0; s != n; s++)
        {
            if (book[s] == u_input[n])
            {
                printf("Invalid key: Key contains duplicate value.\n");
                return 3;
            }

        }

    }
    return 0;
}