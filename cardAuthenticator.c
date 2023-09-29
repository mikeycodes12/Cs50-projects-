//a program that prompts the user for a credit card number 
//and then reports (via printf) whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein
// input Number: 4003600000000014 user prompted to input their cc number 
// ouput: VISA/mastercard/invalid - used told whether cc is valid and the brand isbased on input number and luhns algorithm
#include <cs50.c>
#include <stdio.h>
#include <math.h>
int main(void)

{
    int firsttwodigits;
    long divisor = 10;
    int length = 0;
    int firstdigits;
    int twoxversion;
    int lastdigit;
    long correctcc1;
    long correctcc;
    long cardnumber;
    int sum = 0;// decleration of variable type

  do
 {
   cardnumber = get_long("what is your creditcardnumber?:"); //prompt for user
 }
 while (cardnumber <= 0 ); // reprompt while number is less than or equal to zero-change to be specific ?

   correctcc = cardnumber; // assigment of unchanged input cardnumber to correct cc

 while(correctcc > 0) // while input is larger than zero
{
  lastdigit = correctcc % 10; // first part of luhns algorithm  find last digit
  sum = sum + lastdigit; // sum of every other digit
  correctcc = correctcc/100;// divide input by 100 to move two digits along
}
  correctcc1 = cardnumber/10; // second part of luhns algorithm
  while(correctcc1 > 0)
{
 lastdigit = correctcc1 % 10;
 twoxversion = lastdigit*2;
 sum = sum + (twoxversion/10)+(twoxversion%10);
 correctcc1 = correctcc1/100;
}
  correctcc = cardnumber; // assigment of variable
  while(correctcc!= 0)
{
  correctcc = correctcc / 10; //variable in loop body 'correctcc divided by 10 with counter that increments to find length
  length++;
}
for (int i = 0; i < length - 2; i++ ) // loop that divides number to find first digits-for loop set lenght -2 times
{
  divisor = divisor * 10; // creation of divisor 10 * 10 LOOPED LENGTH -2 TIMES OR TO POWER OF
}
firstdigits = cardnumber / divisor;
firsttwodigits = cardnumber / (divisor / 10); // assigment of digits

if (sum % 10 == 0) // check sum using if/else loops checking against conditions caculated
{
    if (( length == 15) && (firsttwodigits == 34 || firsttwodigits == 37 ))
   {
      printf("valid american express\n");
   }

   else if ((length == 16) && (firsttwodigits > 50 && firsttwodigits < 56))

   {
      printf("valid mastercard \n");
   }

   else if ((length == 13 || length == 16 ) && ( firstdigits == 4))
   {
      printf("valid visa\n");
   }
   else
   {
   printf("invalid\n");
   }
}
}
