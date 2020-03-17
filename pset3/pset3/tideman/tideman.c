#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) /* go thru all the candidate*/
    {
        if (strcmp(candidates[i], name) == 0) /* if candidate name matches*/
        {
            ranks[rank] = i; /* place the candidate id as the rank*/
            return true;
        }
    }
    return false; /* no rank updated*/
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < (candidate_count - 1); i++) /* go thru all candidates id*/
    {
        for (int j = i + 1; j < candidate_count; j++) /* array goes after i candidate id*/
        {
            preferences[ranks[i]][ranks[j]]++; /*increment the preference array value*/
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int array_index = 0; /* make array index variable*/

    for (int i = 0; i < (candidate_count - 1); i++) /* go thru all candidates id*/
    {
        for (int j = i + 1; j < candidate_count; j++) /* array goes after i candidate id*/
        {
            if (preferences[i][j] > preferences[j][i]) /* if i > j*/
            {
                pair this_pair; /* make this pair instance*/
                this_pair.winner = i; /* winner to i*/
                this_pair.loser = j; /* loser to j*/
                pairs[array_index] = this_pair; /* set this pair to the pair index*/
                array_index++; /* increase the array index*/
                pair_count++; /* increase the pair count*/
            }
            else if (preferences[j][i] > preferences[i][j]) /* vice versa*/
            {
                pair this_pair;
                this_pair.winner = j;
                this_pair.loser = i;
                pairs[array_index] = this_pair;
                array_index++;
                pair_count++;
            }
            else
            {
                /* Do nothing*/
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temporary_pair; /* place holder for the swap*/
    for (int i = 1; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i; j++)
        {
            if (pairs[j].loser < pairs[j + 1].loser) /*if first pair is less than the other*/
            {
                /* swap process*/
                temporary_pair = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temporary_pair;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int win = 0; /* variable for win*/
    int lose = 0; /* variable for lose*/

    for (int i = 0; i < pair_count; i++) /* go thru the pairs*/
    {
        locked[pairs[i].winner][pairs[i].loser] = true; /* let locked as true*/
        win += pairs[i].winner; /*increase win*/
        lose += pairs[i].loser; /*increase lose*/
        if (win == lose)
        {
            locked[pairs[i].winner][pairs[i].loser] = false; /*if win and lose pairing equal, make locked false*/
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) /* go thru all the rows in locked array*/
    {
        int sum = 0; /*variable for sum*/
        for (int j = 0; j < candidate_count; j++) /*go thru all the column in locked array*/
        {
            if (locked[j][i] == false)
            {
                sum++; /*increase sum if locked is false*/
            }
            if (sum == candidate_count)
            {
                printf("%s\n", candidates[i]); /* print winner if sum equals candidate count*/
                return;
            }
        }
    }
    return;
}

