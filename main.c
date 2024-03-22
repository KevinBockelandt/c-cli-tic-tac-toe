#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 9

// Initialize the content of the board with spaces
void initBoard(char *b) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    *(b+i) = ' ';
  }
};

// Print out the current content of the board on screen
void printBoard(char *b) {
  printf("\n");
  printf("  A   B   C\n");
  printf("-------------\n");
  printf("| %c | %c | %c | 1\n", *(b + 0), *(b + 1), *(b + 2));
  printf("-------------\n");
  printf("| %c | %c | %c | 2\n", *(b + 3), *(b + 4), *(b + 5));
  printf("-------------\n");
  printf("| %c | %c | %c | 3\n", *(b + 6), *(b + 7), *(b + 8));
  printf("-------------\n");
  printf("\n");
};

// Return the index in the board array for the cell with specified coordinates
int getIndexFromInput(char col, char row) {
  int x = col == 'A' ? 0 : (col == 'B' ? 1 : 2);
  int y = row == '1' ? 0 : (row == '2' ? 1 : 2);

  return x + (3 * y);
}

// Make sure the user input is valid
// Return 0 if everything OK
int checkInput(char *b, char col, char row) {
  if (
    (col != 'A' && col != 'B' && col != 'C') ||
    (row != '1' && row != '2' && row != '3')
  ) {
    printf("The input must be the column letter followed by the row number.\n");
    printf("Ex: 'A3' or 'B2'\n");
    return 1;
  }
  else if (*(b + getIndexFromInput(col, row)) != ' ') {
    printf("The specified cell is not empty.\n");
    return 1;
  }

  return 0;
}

int main() {
  // The content of the board is handled by an array where each cell can contain:
  // - ' ' (space) - when nothing has been played there yet
  // - 'X' (cross) - when the player claimed that cell
  // - 'O' (circle) - when the game claimed that cell
  char board[BOARD_SIZE];
  initBoard(board);

  // Different from 0 if we should stop the game
  short shouldStop = 0;

  // Used to hold the input of the player for the next move
  char userInput[3];

  // Main loop that will run until the game is over
  while (shouldStop == 0) {
    printBoard(board);
    fgets(userInput, sizeof(userInput), stdin);

    if (checkInput(board, userInput[0], userInput[1]) == 0) {
      board[getIndexFromInput(userInput[0], userInput[1])] = 'X';
    }

    // need to flush the input buffer otherwise fgets will not behave properly
    int cFlush;
    while ((cFlush = getchar()) != '\n' && cFlush != EOF) {}
  }

  return 0;
};
