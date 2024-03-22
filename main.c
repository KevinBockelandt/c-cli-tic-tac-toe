#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 9

// Coordinates for a board cell.
typedef struct {
  char col;
  char row;
} Coordinates;

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
int getIndexFromCoordinates(Coordinates inCoor) {
  int x = inCoor.col == 'A' ? 0 : (inCoor.col == 'B' ? 1 : 2);
  int y = inCoor.row == '1' ? 0 : (inCoor.row == '2' ? 1 : 2);

  return x + (3 * y);
}

// Return the index in the board array for the cell with specified coordinates
Coordinates getCoordinatesFromIndex(int index) {
  Coordinates retCoord;
  int rowNum = round(index / 3);
  int colNum = index % 3;

  retCoord.col = colNum == 0 ? 'A' : (colNum == 1 ? 'B' : 'C');
  retCoord.row = rowNum == 0 ? '1' : (rowNum == 1 ? '2' : '3');

  return retCoord;
}

// Make sure the user input is valid
// Return 0 if everything OK
int checkInput(char *b, Coordinates inCoor) {
  if (
    (inCoor.col != 'A' && inCoor.col != 'B' && inCoor.col != 'C') ||
    (inCoor.row != '1' && inCoor.row != '2' && inCoor.row != '3')
  ) {
    printf("The input must be the column letter followed by the row number.\n");
    printf("Ex: 'A3' or 'B2'\n");
    return 1;
  }
  else if (*(b + getIndexFromCoordinates(inCoor)) != ' ') {
    printf("The specified cell is not empty.\n");
    return 1;
  }

  return 0;
}

// Ask for user input and perform their move
void playerMove(char *board) {
  // Value 1 when the move is validated and performed
  int moveOk = 0;
  // Holds the string for the user input
  char userInput[3];

  while (moveOk == 0) {
    printf("Your move:\n");
    fgets(userInput, sizeof(userInput), stdin);

    Coordinates inputCoor = { userInput[0], userInput[1] };

    if (checkInput(board, inputCoor) == 0) {
      int boardIndex = getIndexFromCoordinates(inputCoor);
      *(board + boardIndex) = 'X';
      moveOk = 1;
    }

    // need to flush the input buffer otherwise fgets will not behave
    // properly since we are using it in a loop
    int cFlush;
    while ((cFlush = getchar()) != '\n' && cFlush != EOF) {}
  }

  printBoard(board);
}

// Perform the move of the game AI
void gameMove(char *board) {
  printf("Game move:\n");

  // TODO find a more interesting way than just using the first empty cell
  for(int i = 0; i < BOARD_SIZE; i++) {
    if (*(board + i) == ' ') {
      *(board + i) = 'O';
      Coordinates moveCoord = getCoordinatesFromIndex(i);
      printf("%c%c\n", moveCoord.col, moveCoord.row);
      printBoard(board);
      return;
    }
  }

  // if we reach this point, we could not find any empty cell
  printf("Internal error. No empty cells left\n");
  exit(0);
}

// Check if either the player or the game won and act upon it
// Return 1 if the game should stop. 0 otherwise
int checkForCompletion(char *board) {
  // printf("You win! Congratulations :)");
  // printf("You lose :/");
  // printf("It's a tie! :|");
}

int main() {
  // Different from 0 if we should stop the game
  short shouldStop = 0;

  // The content of the board is handled by an array where each cell can contain:
  // - ' ' (space) - when nothing has been played there yet
  // - 'X' (cross) - when the player claimed that cell
  // - 'O' (circle) - when the game claimed that cell
  char board[BOARD_SIZE];
  initBoard(board);
  printBoard(board);

  // Main loop that will run until the game is over
  while (shouldStop == 0) {
    playerMove(board);
    // shouldStop = checkForCompletion(board);
    gameMove(board);
    // shouldStop = checkForCompletion(board);
  }

  return 0;
};
