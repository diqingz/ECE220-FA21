#include <stdlib.h>
#include <stdio.h>
/*partner: staceyl2
 ERRORS:
   ERROR1: is_prime function:return value wrong (returning 0 when number is prime)
   fixed: change 0 into 1 in line21, 1 into 0 in line 18
   ERROR2: print_semiprimes function: using i%j as k value (should actually use the quotient as k value, thus change into i/j)
   ERROR3: print_semiprimes function: printing some of the semiprimes twice because in the cases of when both prime numbers(that multiplies into a semiprime) are within the range.  e.g. 2*3 = 6, 3*2 = 6 with input numbers 2, 6.
   Fix by breaking the function when it realizes the current i value is the same as the former one in the nested loop.

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int x = 0;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
		    
                    if (is_prime(k)) {
		      if (x == i){
		      break;}
		      x = i;
                        printf("%d ", i);
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
