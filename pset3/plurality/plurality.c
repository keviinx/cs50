#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++) /* go thru the candidate array*/
    {
        if (strcmp(candidates[i].name, name) == 0) /* candidate name matches with vote*/
        {
            candidates[i].votes++; /*increase the vote count*/
            return true; /* return true*/
        }
    }
    return false; /*name not found return false*/
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int largest_vote_count = 0; /* largest vote count variable*/

    for (int i = 0; i < candidate_count; i++) /*go thru all the vote number to see the largest vote count*/
    {
        if (candidates[i].votes > largest_vote_count) /* if the vote number is larger*/
        {
            largest_vote_count = candidates[i].votes; /* set the largest vote count variable to that value*/
        }
    }

    for (int i = 0; i < candidate_count; i++) /*go thru the candidates again*/
    {
        if (candidates[i].votes == largest_vote_count) /*compare the largest value with every candidate*/
        {
            printf("%s\n", candidates[i].name); /*print the name of the winner*/
        }
    }

    return;
}