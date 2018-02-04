#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char HANG_STATES[7][10 * 9] = 
{
	"             +         +----     +----     +----     +----     +----     +----     +----  ",
	"             |         |         |   O     |   O     |   O     |   O     |   O     |   O  ",
	"             |         |         |         |   +     | --+     | --+--   | --+--   | --+--",
	"             |         |         |         |   |     |   |     |   |     |   |     |   |  ",
	"             |         |         |         |         |         |         |  /      |  / \\ ",
	"             |         |         |         |         |         |         |         |      ",
	"/*****\\   /*****\\   /*****\\   /*****\\   /*****\\   /*****\\   /*****\\   /*****\\   /*****\\   "
};

int main(int argc, char *argv[]) {
  /* Your code here */

  int clear = 0;

  /* BREAK DOWN PROBLEM INTO RUDEMENTARY PROBLEMS */


  // keep looping until one of three things happen
  // read in user input
  // games needs to be able to respond to said input
	// print the game's UI
  // Store all guessed letters (in an array?)
  // need to be able to handle individual letter guesses and word guesses
  // ability to exit out of the game
  // Print the game ui

  /* SN: argc counts the program itself as an argument so argc starts at 1 even if there is no word passed when beginning the game */

  // Check if no input was passed to our program
  if (argc == 1) {
	  printf("Usage: %c [-c] word\n", argv[0]) // Access the programs name by using argv[0] 
	  return 1; // use non-zero exit status to represent error
  }

  // check if the user typed in a flag (hangman keyword)
  if (argv[1][0] == '-') { // NOTE!!! the "[0]" represents the first character of what is in argv[1] 
	// Check if user typed in the `-c` flag
	if (argv[1][1] == 'c') {
		// clear the screen
		clear = 1;
	}
  } 

  
  
  return 0;
}