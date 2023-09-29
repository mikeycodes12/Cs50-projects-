//In the plurality vote, every voter gets to vote for one candidate. 
//At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election.

// example - ./plurality Alice Bob - number of candidates in command line argument
//Number of voters: 3 - user prompted for number of voters
//Vote: Alice  - user prompted to put in candidate they voted for
//Vote: Bob
//Vote: Alice
//Alice wins ! - ouput of winner 



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
    int count = 0;

    for( int i = 0 ; i < candidate_count; i++)
{
    if(strcmp (candidates[i].name , name) == 0) //iterates though array to compare with user input
    {
        candidates[i].votes ++ ; // updates votes array if user input matches array
        count ++ ;
    }
}
 if (count > 0)
    return true;
 else
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
 int top_vote = candidates[0].votes; // intialisation of topvote - first element of array
 for(int i = 0 ; i < MAX ; i++)
 {
        if( top_vote < candidates[i].votes)
        {
            top_vote = candidates[i].votes; // iterative loop that compares each element of array if previous element < next element it replacs it as 'topvote'
        }
 }
    for(int i = 0 ; i < MAX ; i++)
 {
        if (top_vote == candidates[i].votes)
       {
          printf("%s\n",candidates[i].name);
       }
 }
}
