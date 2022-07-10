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
    for (int j = 0; j < candidate_count; j++)
    {
        if (0 == strcmp(candidates[j], name)) {
            // record vote for candidate #j
            ranks[rank] = j;
            return true;
        }
    }
    // no match
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int j = 0; j < candidate_count; j++) {
        for (int k = j + 1; k < candidate_count; k++) {
            preferences[ranks[j]][ranks[k]] ++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int j = 0; j < candidate_count; j++) {
        for (int k = j + 1; k < candidate_count; k++) {
            int score = preferences[j][k] - preferences[k][j];
            if (score != 0) {
                if (score > 0) {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = k;
                    preferences[j][k] = score;
                } else {
                    pairs[pair_count].winner = k;
                    pairs[pair_count].loser = j;
                    preferences[k][j] = -score;
                }
                pair_count ++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int j = 0; j < pair_count; j++) {
        for (int k = 0; k < pair_count - j - 1; k++) {
            if (preferences[pairs[k].winner][pairs[k].loser] <
                preferences[pairs[k + 1].winner][pairs[k + 1].loser]) {

                pair tmp = pairs[k];
                pairs[k] = pairs[k + 1];
                pairs[k + 1] = tmp;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int check[candidate_count]; // deq of candidates to check cycles
    int check_lo, check_up;

    for (int j = 0; j < pair_count; j++) {
        bool skip_pair = false;
        check_lo = 0;
        check_up = 1;
        check[0] = pairs[j].loser;
        while (check_lo < check_up) {
            if (locked[check[check_lo]][pairs[j].winner]) {
                // cycle - skip this pair
                skip_pair = true;
                break;
            } else {
                for (int k = 0; k < candidate_count; k ++) {
                    if ( locked[check[check_lo]][k] ) {
                        check[check_up] = k;
                        check_up ++;
                    }
                }
            }
            check_lo ++;
        }
        if (!skip_pair) {
            locked[pairs[j].winner][pairs[j].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j ++) {
        bool winner = true;
        for (int k = 0; k < candidate_count; k ++) {
            if (locked[k][j]) {
                winner = false;
                break;
            }
        }
        if (winner) {
            printf("%s\n", candidates[j]);
            return;
        }
    }
}

