#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++) /* go thru all the candidate count*/
    {
        if (strcmp(candidates[i].name, name) == 0) /*if the name matches*/
        {
            preferences[voter][rank] = i; /*update and rank preference*/
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++) /*go thru the votes based on the voter count*/
    {
        for (int j = 0; j < candidate_count; j++) /*go thru each preferences*/
        {
            if (candidates[preferences[i][j]].eliminated != true) /*if candidate is still in the run*/
            {
                candidates[preferences[i][j]].votes++; /*increase vote count*/
                break; /*go to the next vote ballot*/
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) /* go thru all the candidate*/
    {
        if (candidates[i].votes > voter_count / 2) /* if any candidate have more than half majority*/
        {
            printf("%s\n", candidates[i].name); /*print candidate's name, NEED \n HERE?!*/
            return true; /*return true*/
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimum_vote = voter_count; /* set the minimum vote to the highest first*/

    for (int i = 0; i < candidate_count; i++) /* go thru all candidates*/
    {
        if (candidates[i].eliminated != true
            && candidates[i].votes < minimum_vote) /* if not eliminated and vote count lower than minimum vote*/
        {
            minimum_vote = candidates[i].votes; /* set that vote count to minimum vote*/
        }
    }

    return minimum_vote; /* return the minimum vote*/
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool is_tie = true; /* set condition to tie directly*/

    for (int i = 0; i < candidate_count; i++) /*go thru all the candidates*/
    {
        if (candidates[i].eliminated != true && candidates[i].votes != min) /* if not eliminated and not same vote as min vote*/
        {
            is_tie = false; /* set tie condition to false*/
        }
    }

    return is_tie; /* return tie condition*/
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++) /* go thru all the candidates*/
    {
        if (candidates[i].eliminated != true && candidates[i].votes == min) /* if the candidate is not eliminated and have the lowest vote*/
        {
            candidates[i].eliminated = true; /* eliminate the candidate*/
        }
    }
    return;
}
