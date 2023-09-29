
//In a substitution cipher, we “encrypt” (i.e., conceal in a reversible way)
//a message by replacing every letter with another letter. To do so,
//we use a key: in this case, a mapping of each of the letters of the alphabet to the letter 
//it should correspond to when we encrypt it. To “decrypt” the message, the receiver of the message 
// would need to know the key, so that they can reverse the process: translating the encrypt text (generally called ciphertext)

// - Example
//./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO - command line arguement acts as key (in this example ABC corresponds to YTN)
//plaintext:  HELLO - user input text 
//ciphertext: EHBBQ - rotated ciphertext based on key 

#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string string_rotate(string plntxt, string key1); // declaration of prototype functions which takes two string arguments(input key/input string)

int repeat_char_check(string s); // declaration of prototype function thats takes one string argument (checks for repeating characters in key)

int main(int argc, string argv[]) // int main that takes command line argument
{

if( argc != 2) // if function that prints error message if arguement is not 2 ie  ./ substitution *key*
{
 printf ("Usage:./ substitution key \n");
    return 1 ;
}

int arglen = strlen(argv[1]) ; // if function that returns error message if argv[1] ie the key length is not equal to 26 characters

if( arglen != 26)
{
    printf("Key must contain 26 characters\n");
    return 1;
}
 string key = argv[1]; // decleration and intialisation of key and sum
 int sum = 0;

if  (repeat_char_check(key)) // application of repeat char check function on key
 {
    printf("repeating char!\n");
    return 1 ;
 }
    string plaintext = get_string ("plaintext: ");  // prompt user for the key * - USE OF GET STRING ALTENATIVE - CREATE A HELPER FUNCTION 
    string ciphertext = string_rotate (plaintext, key); //calling of string_rotate function on user input
    printf( "ciphertext:%s",ciphertext); // output printed back to user
    free(ciphertext); // malloc function used previously in string_rotate function - freeing of memory block ciphertext
    printf("\n"); // new line printed
    return 0; //exit of main

}

int repeat_char_check(string s)

{
  int seen_char[26] = {0} ; // array of size 26 intilised to zero
  int len = strlen (s); //use of strlen function to check the input string length
  for(int i = 0; i < len; i++) // for loop iterates through string len
{

    if (isalpha(s[i])) // checks if input is alpha - note s[i] is the string character at postion i
   {
    int index = tolower(s[i]) - 'a'; // converts s[i]- character at i to lowercase then subtracts 'a' to find index value that corresponds to the character's position in the alphabet
    if (seen_char[index] ) // array seen_char[index] intialised to zero ie if(0) statement is false and will not run - note this can be done with a count function or boolean
     {
     // returns 1 if seen_char[i] = 1 ie true as there is a repeated character - loop ends
       return 1;
     }
    seen_char[index] = 1; // seen_char array updated if character is not repeated, if character is repeated its index value will aligned with 1 and flagged as a repeating char
   }

}
  return 0;// set outside for loop!
}
string string_rotate (string plntxt ,string key1)
 {
   int len = strlen(plntxt);
   string cipher = malloc(len + 1); // cipher dynamically allocated using malloc and number of bytes ie len + 1(string ends in 0) pointer returned to beginning of the block
   int x;
   int pln_index[len]; // array of unkown size len - no intilisation as size unknown
   int key_index[26] = {0};
   int shift;

    for (int j = 0 ; j < 26; j++ ) // loop to populate index array
  {
    key_index[j] = (tolower(key1[j]) - 'a')%26; // index of size 26 populated with index values of the key , use of modulus to avoid negative values and loop round
  }
  for (int i = 0 ; i < len ; i++ ) // for loop iterates over the string input
  {
   if (isalpha(plntxt[i]))// if a character ie plntext[i] is alphabetical
     {
      if (islower(plntxt[i])) // if a character ie plntext[i] is lowercase
     {
      x = 'a';
     }
      else
     {
      x = 'A';
     }
   pln_index[i] = plntxt[i]- x; // getting plntext index by - x
  shift = (key_index[pln_index[i]] - pln_index[i])%26; // shift is difference between key index thats at the same position as plnindex - plnindex value  , use of modulus to loop over
  cipher[i] = ((pln_index[i] + shift) %26 ) + x;
    }
else
{
  cipher[i] = plntxt[i] ; // non alpahabetical characters remain unchanged by the key
}}
cipher[len] = '\0'; // as cipher is a string last byte is \0 (null terminator) ie len in which len is the last character
return cipher; // function returns cipher , note this needs to be freed in main as the malloc function was used prior to prevent memory leaks.
}
