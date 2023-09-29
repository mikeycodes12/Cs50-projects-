
//A simple scrabble for two players
//Player 1: COMPUTER  - user 1 prompted for word 
//Player 2: science    - user 2 prompted for word
//Player 1 wins!      - based on characters used and corresponding score , winner is output



#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};


int compute_score(string word);// prototype fuction

int main(void)
{
    string word1 = get_string("Player 1: ");// user prompt assigning input to variables word1/word2
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1); // declaration - application of helper fucntion compute score
    int score2 = compute_score(word2);
{
   if (score1 > score2) // if else loop comparing variables
   {
    printf("player 1 wins!\n");
   }
   else if (score2 > score1)
   {
   printf("player 2 wins!\n");
   }
   else
   {
   printf("its a draw\n");
   }
 }
} // end of main function
int compute_score(string word) // compute_score function that is used in main to caculate score

  int len = strlen(word);
  int score = 0; // intialise variables

  for (int i = 0 ; i < len ; i++) // for loop used to iterate through user input- stops at end of string
{
    if (isupper(word[i])) // if argument used to determine if input char is uppercase (use of issupper function)
  {
     score = score + POINTS[word[i]-65];// if char is upper case ascii value taken away- this aligns with alphabetical placing in array-hence indexes into the array(word[i]-65 = index postion)
  }

 else if (islower(word[i]))
  {
     score = score + POINTS[word[i]- 97];
  }
}
{
  return score; // score variable " returned" to int main where function is called
}
