#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text); /* function for counting letters*/
int count_words(string text); /* function for counting words*/
int count_sentences(string text); /* function for counting sentences*/;

int main(void)
{
    float l; /* variable for letters*/
    float s; /* variable for sentences*/
    float w; /* variable for words*/
    int index; /*variable for index*/

    string text = get_string("Text: "); /* prompt the user for text*/
    l = count_letters(text); /*get letters count*/
    s = count_sentences(text); /* get sentences count*/
    w = count_words(text); /* get words count*/
    index = round(0.0588 * (100 * l / w) - 0.296 * (100 * s / w) - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index); /*print out the grade index*/
    }

}

int count_letters(string text)
{
    int letter_count = 0; /* variable for letter count*/
    int letter_count_counter = 0; /* counter to go through the text*/

    while (text[letter_count_counter] != '\0')
    {
        if (islower(text[letter_count_counter]) || isupper(text[letter_count_counter])) /* check whether it is alphabet*/
        {
            letter_count++; /*increase the count*/
        }
        letter_count_counter++; /*increase the array count*/
    }

    return letter_count; /*return the letter count*/
}

int count_words(string text)
{
    int word_count = 0; /* variable for storing the word count*/
    int word_count_counter = 0; /* counter to go thru the text*/

    while (text[word_count_counter] != '\0')
    {
        if (isspace(text[word_count_counter])) /* check whether it is a space*/
        {
            word_count++; /*increase the count*/
        }
        word_count_counter++; /*increase the array count*/
    }
    word_count++; /* there is no space for the last word, so +1*/

    return word_count; /*return the word count*/
}

int count_sentences(string text)
{
    int sentence_count = 0; /* variable for sentence count*/
    int sentence_count_counter = 0; /* counter to go thru the text*/

    while (text[sentence_count_counter] != '\0')
    {
        if (text[sentence_count_counter] == '.' || text[sentence_count_counter] == '!'
            || text[sentence_count_counter] == '?') /* check for punctuation*/
        {
            sentence_count++; /*increment the sentence count*/
        }
        sentence_count_counter++; /* increase the array counter*/
    }

    return sentence_count; /*return the sentence count*/
}