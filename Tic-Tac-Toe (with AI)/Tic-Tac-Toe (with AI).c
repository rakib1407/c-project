#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];  // Tic-Tac-Toe board
char player = 'X', computer = 'O';  // Player and Computer markers

// Function to initialize the game board with empty spaces
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the Tic-Tac-Toe board
void printBoard() {
    printf("\nTic-Tac-Toe Board:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
}

// Function to check if the game has a winner
int checkWinner(char mark) {
    // Check rows, columns, and diagonals for a winning condition
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) return 1;
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark) return 1;
    }
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) return 1;
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) return 1;
    
    return 0;
}

// Function to check if the board is full (draw condition)
int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return 0;  // If there's any empty space
        }
    }
    return 1;  // Board is full
}

// Function to allow the player to make a move
void playerMove() {
    int row, col;
    printf("Enter your move (row and column [0-2]): ");
    scanf("%d %d", &row, &col);
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = player;
    } else {
        printf("Invalid move! Try again.\n");
        playerMove();
    }
}

// Function to allow the computer to make a move (AI)
void computerMove() {
    int row, col;
    srand(time(0));  // Initialize random seed
    do {
        row = rand() % 3;  // Random row
        col = rand() % 3;  // Random column
    } while (board[row][col] != ' ');  // Repeat if the cell is already taken
    
    board[row][col] = computer;
    printf("Computer chooses: %d %d\n", row, col);
}

// Main function to control the game
int main() {
    int turn = 0;  // 0 for player, 1 for computer
    initializeBoard();  // Initialize the game board
    
    while (1) {
        printBoard();  // Print the current state of the board
        
        if (turn % 2 == 0) {
            playerMove();  // Player's turn
        } else {
            computerMove();  // Computer's turn
        }
        
        // Check if the player or computer wins
        if (checkWinner(player)) {
            printBoard();
            printf("Congratulations! You win!\n");
            break;
        } else if (checkWinner(computer)) {
            printBoard();
            printf("Computer wins! Better luck next time.\n");
            break;
        } else if (isBoardFull()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
        
        turn++;
    }
    
    return 0;
}
