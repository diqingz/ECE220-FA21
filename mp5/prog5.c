/*
   prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
             student code -- GOLD VERSION by Steven S. Lumetta
    (The functions set_seed, start_game and make_guess are defined in the header file). 

    Intro paragraph: 
    This program mimics the board game Mastermind, generates a random sequence of 4 numbers from 1-8 using a user input seed. 
    The user has 12 guesses to win the game. In the process, the game will tell how many perfect and misplaced matches were made. 

    Partners: staceyl2, mohan19
 */


#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
      int seed;
      char post[2];
//    The sscanf statement below reads the integer into seed, everything else will go to post. 
      int sscanfRet = sscanf (seed_str, "%d%1s", &seed, post);
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 

      if (sscanfRet == 1) {
          srand(seed);
          return 1;
      }
    printf("set_seed: invalid seed\n");
    return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    guess_number = 1;

    // make random nunbers that in range 1-8.
    solution1 = rand() % 8 + 1;
    solution2 = rand() % 8 + 1;
    solution3 = rand() % 8 + 1;
    solution4 = rand() % 8 + 1;

    // set the content of the addresses one-four to the solutions
    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
    // read 4 integers from user guess input, everything else will go to post.
    char post[2]; 
    int sscanfRet = sscanf (guess_str, "%d%d%d%d%1s", one, two, three, four, post);
    int guessArr[4];
    guessArr[0] = *one;
    guessArr[1] = *two;
    guessArr[2] = *three;
    guessArr[3] = *four;

    int solArr[4];
    solArr[0] = solution1;
    solArr[1] = solution2;
    solArr[2] = solution3;
    solArr[3] = solution4;

    // 1 means paired, 0 means unpaired.
    int guessPaired[] = {0,0,0,0}; 
    int solPaired[] = {0,0,0,0};


    int perfMatch = 0;
    int misplacedMatch = 0;
    
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
    if (sscanfRet == 4) {
        if (*one >= 1 && *one <= 8 && *two >= 1 && *two <= 8 && *three >= 1 && *three <= 8 && *four >= 1 && *four <= 8) {
            // perfect match
            for (int i = 0; i < 4; i++) {
                if (guessArr[i] == solArr[i]) {
                    perfMatch ++;
                    guessPaired[i] = 1;
                    solPaired[i] = 1;
                }
            }
            
            // misplaced match
            for (int i = 0; i < 4; i++) {
                if (guessPaired[i] == 0) {
                    for (int j = 0; j < 4; j++) { // j is for the solution index
                        if (guessArr[i] == solArr[j] && solPaired[j] == 0) {
                            misplacedMatch ++;
                            guessPaired[i] = 1;
                            solPaired[j] = 1;
                            break;
                        }
                    }
                }
            }

            printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfMatch, misplacedMatch);
            guess_number ++;
            return 1;
        }
    }

    printf("make_guess: invalid guess\n");
    return 0;
}
