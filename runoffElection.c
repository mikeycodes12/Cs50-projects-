//ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate. 
//Instead of just voting for their top choice, they can rank the candidates in order of preference.
//./runoff Alice Bob Charlie - candidates required in command line arguement 
// Number of voters: 5  - user prompted for number of voters
// Rank 1: Alice        - each voter ranks a candidate
// Rank 2: Charlie
// Rank 3: Bob

// Rank 1: Alice
// Rank 2: Charlie
// Rank 3: Bob

// Rank 1: Bob
// Rank 2: Charlie
// Rank 3: Alice

// Rank 1: Bob
// Rank 2: Charlie
// Rank 3: Alice

// Rank 1: Charlie
// Rank 2: Alice
// Rank 3: Bob

// Alice wins! - output of winner based on the preferences of voters 



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

    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES); //input checks
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)// Populate array of candidates
    {
        candidates[i].name = argv[i + 1]; // assignment of user input
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: "); // assignment of user input
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) //iterate through index of voters
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1); // iterating through in which j is the index of current candidate (note its j+1 as ranking starts at 1 but index starts at zero)
            // Record vote, unless it's invalid
            if (!vote(i, j, name))  // name checked against commmand line arguement names
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
    for( int i = 0 ; i < candidate_count ; i++)
    {
        if(strcmp (candidates[i].name , name) == 0) //iterates though array to compare with user input using strcmp
        {
         preferences[voter][rank] = i; // global preferences array updated - in which i is the candidate name index
         return true; // return true if valid vote
        }
    }
    return false;
}
// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
   for (int i = 0 ; i < voter_count ; i++ )
   {
     for (int j = 0 ; j < candidate_count ; j++)
     {

      if (!candidates[preferences[i][j]].eliminated) // check candidate corresponding to the current preference (preferences[i][j]) has been eliminated
        {
         candidates[preferences[i][j]].votes ++; //+1 added to votes
         break ; // break out of  inner candidate loop and move onto next voter
        }
      }
   }
}
// Print the winner of the election, if there is one
bool print_winner(void)
{
    for ( int i = 0 ; i < candidate_count; i++)
    {
        if(candidates[i].votes > voter_count/2) // if votes for candidate i exceed 1/2 print candidate name
        {
            printf("%s\n",candidates[i].name);
            return true;
        }
   }
 return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
int min_vote = INT_MAX;
 for (int i = 0 ; i < candidate_count ; i++)
 {
  if((!candidates[i].eliminated && candidates[i].votes < min_vote)) // checks current candidate has not been eliminated and compares agains first candidates vote
     {
        min_vote = candidates[i].votes ; // min vote updated if both conditions met
     }
 }
  return min_vote;
}
// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
  int not_eliminated = 0;
  int tie = 0;
  for (int i = 0 ; i < candidate_count ; i++)
 {
  if (!candidates[i].eliminated)
    {
              not_eliminated ++; // updates for non eliminated candidates
    }
 if (candidates[i].votes == min)
    {
                 tie ++;   // updates for those who have minimun score
    }
  }
 if( tie == not_eliminated) // comparison of non eliminated to those with minimum score
  {
     return true;
  }
     return false;
}



// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
 for (int i = 0 ; i < candidate_count ; i++)
 {
    if(candidates[i].votes == min)
   {
    candidates[i].eliminated = true ;
   }
 }
}