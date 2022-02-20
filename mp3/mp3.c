#include <stdio.h>
#include <stdlib.h>


/*intro paragraph: 
partner netid: staceyl2
count---used as counter for factorial function
result---return value of factorial function
row---the entered value of row index
n---store the entered value of row index,just to match the function given
k---the current count of coefficient on the row

This program asks the user for a row index input and then prints out all the coefficients in the row from pascal's triangle. 

 */
long factorial(int i)
{
  //factorial function to calculate factorial for an input i
  int count;
  long result = 1;


  for (count = 1; count <= i; count++ ){
    result = result *count;
  }
    return (result);
  
}
int main()
{
  //main function 
  //scans user input and print the calculated coefficients to the screen
  int row;
  int n;
  int k;

  printf("Enter a row index: ");
  scanf("%d",&row);

  n = row;
  
  for (k = 0; k <= n; k++){
    printf("%lu", factorial(n)/(factorial(k)*factorial(n-k)));
    printf(" ");

}
  

  

  return 0;
}
