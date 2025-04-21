#include <cs50.h>
#include <stdio.h>
#include <string.h>


#define MAX_VOTERS 100
#define MAX_CANDIDATES 9


int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

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
    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            // printf("%i", preferences[voter][0]);
            // printf("%i", preferences[voter][1]);
            // printf("%i", preferences[voter][2]);
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int voter_number = 0; voter_number < voter_count; voter_number++)
    {
        for (int voter_rank_number = 0; voter_rank_number < candidate_count; voter_rank_number++)
        {
            bool has_voted = false;
            for (int candidate_number = 0; candidate_number < candidate_count; candidate_number++)
            {
                if (preferences[voter_number][voter_rank_number] == candidate_number &&
                    !candidates[candidate_number].eliminated)
                {
                    candidates[candidate_number].votes++;
                    has_voted = true;
                    break;
                }
            }
            if(has_voted)
            {
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for(int i=0;i<candidate_count;i++)
    {
        if(candidates[i].votes > (voter_count / 2))
        {
            printf("The Winner is %s\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = candidates[0].votes;
    for(int current_candidate_number = 0; current_candidate_number < candidate_count; current_candidate_number++)
    {
        if(!candidates[current_candidate_number].eliminated)
        {
            if(candidates[current_candidate_number].votes < min)
            {
                min = candidates[current_candidate_number].votes;

            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool are_tied = true;
    for(int current_candidate_number = 0; current_candidate_number < candidate_count; current_candidate_number++)
    {
        if(candidates[current_candidate_number].votes != min)
        {
            are_tied = false;
        }
    }
    return are_tied;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for(int current_candidate_number = 0; current_candidate_number < candidate_count; current_candidate_number++)
    {
        if(candidates[current_candidate_number].votes == min)
        {
            candidates[current_candidate_number].eliminated=true;
        }
    }
    return;
}
