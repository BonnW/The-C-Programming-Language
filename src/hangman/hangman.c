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

int str_contains(char *str, char target) {
  return (strchr(str, target) == NULL ? 0 : 1);
}

void print_ui(char *word, char *guessed, int hangman_state, int clear) {
  // if clear flag is set to 1 (true), clear the screen
  if (clear) {
    printf("\033[2J\003[1;1H");
    fflush(stdout);
  }

  // print the current hangman state
  for (int i = 0; i < 7; i++) {
    printf("%.10s\n", &HANG_STATES[i][hangman_state * 10]);
  }
  printf("\n");

  // print guessed letters
  for (int i = 0; i < strlen(word); i++) {
    if (i > 0) {
      printf(" ");
    }
    if (str_contains(guessed, word[i])) {
      printf("%c", word[i]);
    } else {
      printf("_");
    }
  }

  printf("\n\nWrong guesses:\n");

  // find and print missed letters

  for (int i = 0; i < strlen(guessed); i++) {
    if (!str_contains(word, guessed[i])) {
      if (i > 0) {
        printf(" ");
      }
      printf("%c", guessed[i]);
    }
  }
  printf("\n\n");
}

// reads user input from standard input with the given text prompt
char *read_input(char *prompt) {
  size_t s = 1;
  size_t r = 0;
  int c;

  char *in = malloc(sizeof(char) * s);

  printf("%s", prompt);

  // read in the user's input
  while ((c = fgetc(stdin)) != EOF) {
    if ((char)c == '\n') break;
    if (r == s) {
      s *= 2;
      in = realloc(in, s * sizeof(char));
    }
    in[r++] = (char)c;
  }
  in = realloc(in, s * sizeof(char));
  in[r] = '\0';

  return in;
}

int main(int argc, char *argv[]) {
  /* Your code here */

  int clear = 0;
  char *word = NULL;
  char *guessed = NULL;
  char *guess = NULL;

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
    word = argv[2];
  } else {
    word = argv[1];
  }

  // allocate memory to hold guessed letters
  // use calloc instead of malloc since calloc initializes memory with all 0s
  guessed = calloc(strlen(word) + 1, sizeof(char));	

  // print game title
  printf("#################\n");
  printf("#    Hangman    #\n");
  printf("#################\n\n");


  // start game loop
  while(1) {
    // print our UI
    print_ui();

    // read user input
    guess = read_input();

    // handle if the user wants to exit the game
    if (strcmp(guess, "exit") == 0) break; // strcmp == "String Compare"

    // handle word guesses
    if (strlen(guess) > 1) {
      // check the entire guess and check against hangman keyword
      if (strcmp(guess, word) == 0) {
        // correct guess!
        printf("You Win!\n");
        free(guess);
        break;
      } else {
        // incorrect guess 
        printf("No letter\n");
        //increase strick count
        hangman_state++;
      }
    } else {
      // player guessed a single letter
      guessed[guesses++] = guess[0];

      //check to see if the player's guess is a correct one

      if (str_contains(word, guessed[guesses-1])) {
        // if passed, player made a correct guess
        // check to see if they have the whole word
        for (int i = 0, int counter = 0; i < strlen(word); i++) {
          if (str_contains(guessed, word[i])) counter++;
        }
        if (counter == strlen(word)) {
          // player got the whole word
          print_ui();
          printf("Correct! You Win\n");
          free(guess);
          break;
        }
      } else {
        // an incorrect letter guess
        printf("Nope!\n");
        hangman_state++;
      }
    }

    // check to see if the hangman state reached the end
    if (hangman_state == 8) {
      // hangman complete: player loses
      print_ui();
      printf("You lost! The correct word was %s!\n", word);
      free(guess);
      break;
    }

    printf("\n");
  }


  free(guess);
  free(guessed);
  printf("GG WP!\n");
  
  return 0;
}