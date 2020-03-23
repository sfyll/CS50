#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
//Get user's data
{
   float change;
   int q = 25;
   int d = 10;
   int n = 5;
   int p = 1;
   do
   {
       printf("How much change do we how you\n");
       printf("Change: \n");
       change = get_float();
   }
   while( change <= 0 );
//Convert dollars to cents
   int changeone = change * 1000;
   int changei= changeone/10;
   int changef = round(changei);
//proceed to give the coins and count them
   int coin = 0;
   while (changef>=q)
   {
      coin = coin + 1;
      changef = changef - q;
   }
   while (changef>=d)
   {
      coin = coin + 1;
      changef = changef - d;
   }
   while (changef>=n)
   {
      coin = coin + 1;
      changef = changef - n;
   }
   while (changef>=p)
   {
      coin = coin + 1;
      changef = changef - p;
   }
   printf("%d\n", coin);
}
