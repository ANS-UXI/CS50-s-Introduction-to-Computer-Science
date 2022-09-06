#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    double L = ((double) letters / words) * 100.0; // Average number of letters per 100 words
    double S = ((double) sentences / words) * 100.0; // Average number of sentences per 100 words
    double index = (0.0588 * L) - (0.296 * S) - 15.8; // Coleman-Liau index
    int grade = (int) round(index);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letters(string text) // Counts no. of letters
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((int) toupper(text[i]) >= 65 && (int) toupper(text[i]) <= 90) // Checks whether a character is a letter
        {
            count++;
        }
    }
    return count;
}

int count_words(string text) // Counts no. of words
{
    int count = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((int) text[i] == 32) // Checks whether a character is a space
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text) // Counts no. of sentences
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((int) text[i] == 46 || (int) text[i] == 33 || (int) text[i] == 63) // Checks whether a charater is a '!' or '.' or '?'
        {
            count++;
        }
    }
    return count;
}