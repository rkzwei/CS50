#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//prototyping functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main(void)

{
    string user_text = get_string("Text: ");
    //each function does exactly function name and returns value
    int letters = count_letters(user_text);
    int words = count_words(user_text);
    int sentences = count_sentences(user_text);
    //calculates grade level according to Coleman-Liau
    int index = round(0.0588 * (letters / (words / 100.0)) - 0.296 * (sentences / (words / 100.0)) - 15.8);
    //evaluates grading level and prints accordingly
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_sentences(string text)
{
    //basic counting engine used in all functions
    int count = 0;
    int lentot = strlen(text);
    for (int n = 0; n != lentot; n++)
    {
        //counts every sentence according to CS50 specification of sentence
        // 33 is !, 46 is . and 63 is ?
        if (text[n] == 33 || text[n] == 46 || text[n] == 63)
        {
            count++;
        }
    }
    //printf("%i sentences\n", count);
    return count;
}





int count_words(string text)
{
    int count = 0;
    int lentot = strlen(text);
    for (int n = 0; n != lentot; n++)
    {
        //counts word if char is a space and last char is not space and last char is not period
        if (text[n] == 32 && text[n - 1] != 32 && text[n - 1] != 46)
        {
            count++;
        }
        //counts word if char is punctuation and next char is not space and next char is Uppercase and not between quotes
        else if (((text[n] >= 33 && text[n] <= 46) || (text[n] >= 58 && text[n] <= 63)) && text[n + 1] != 32 && (islower(text[n + 1]) == 0)
                 && text[n + 1] != 34)
        {
            count++;
        }
        //counts word if char is at start of sentence
        else if (isupper(text[n]) && text[n - 1] == 32 && text[n - 2] == 46)
        {
            count++;
        }
        //counts word if next char is null
        else if (text[n + 1] == 0)
        {
            count++;
        }

    }
    //printf("%i words\n", count);
    return count;

}




int count_letters(string text)
{
    int count = 0;
    int lentot = strlen(text);
    for (int n = 0; n != lentot; n++)
    {
        //checks if char is alphabetical and counts it
        if (isalpha(text[n]))
        {
            count ++;
        }
    }
    //printf("%i letters \n", count);
    return count;
}