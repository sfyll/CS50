#include <cs50.h>
#include <stdio.h>

int main(void)
//get the input from the user
{
   int height;
   do
   {
       printf("How high should the half pyramid be considered that it must be above an height of 0 and no greater thana height of 23 \n");
       printf("height: \n");
       height = get_int();
   }
   while( height > 23 || height < 0 );
//loop to construct pyramid
   for (int i = 1; i <= height; i++)
   {
       for (int v = 0; v < height - i ; v++)
       {
        printf(" ");
       }
       for (int y = 0; y < i+1; y++)
       {
           printf("#");
       }
       printf("\n");
  // one loop per column
  //inside the loop per column, another one per lign
  //for(x=0, x >= 2, x++){
  //for(y=0, y>= 2, y++){

}
}