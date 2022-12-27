#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Checks winner and Prints the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    // Checks if tie
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    // defines ss as lenght for later use
    int ss = strlen(word);
    // defines array to be used
    string doon = word;
    int scorr = 0;
    // TODO: Compute and return score for string
    for (int n = 0; word[n] != '\0'; n++)
    {
        // lowers casing for scoring
        doon[n] = tolower(word[n]);
    }

    // loops for lenght of word
    for (int s = 0; doon[s] != '\0'; s++)
    {
        // defines value to check against ASCII and POINTS
        int calcval = doon[s];
        // checks if value is a lowercase letter
        if (calcval >= 97 && calcval <= 122)
        {
            // subtracts 97 so that value is between 0 through 25
            int calc = calcval - 97;
            //  adds score
            scorr = scorr + POINTS[calc];
        }
        // if value is not a letter, breaks from loop
        else
        {
            break;
        }
    }
    //printf("%s %i \n", doon, scorr); <<<< debug command
    ss = 0;
    // returns value for evaluation
    return scorr;
}
