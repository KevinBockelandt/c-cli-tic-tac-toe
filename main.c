#include <stdio.h>

#define BOARD_SIZE 9

// Initialize the content of the board with spaces
void initBoard(char *b) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    *(b+i) = ' ';
  }
};

// Print out the current content of the board on screen
void printBoard(char *b) {
  printf("  A   B   C\n");
  printf("-------------\n");
  printf("| %c | %c | %c | 1\n", *(b + 0), *(b + 1), *(b + 2));
  printf("-------------\n");
  printf("| %c | %c | %c | 2\n", *(b + 3), *(b + 4), *(b + 5));
  printf("-------------\n");
  printf("| %c | %c | %c | 3\n", *(b + 6), *(b + 7), *(b + 8));
  printf("-------------\n");
};

int main() {
  // The content of the board is handled by an array where each cell can contain:
  // - ' ' (space) - when nothing has been played there yet
  // - 'X' (cross) - when the player claimed that cell
  // - 'O' (circle) - when the game claimed that cell
  char board[BOARD_SIZE];

  initBoard(board);

  printBoard(board);
  return 0;
};
