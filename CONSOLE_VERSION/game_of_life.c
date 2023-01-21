#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 20

// Function to count the number of live neighbors
int count_neighbors(int grid[ROWS][COLS], int row, int col) {
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i == row && j == col) {
                continue;
            }
            if (i < 0 || i >= ROWS || j < 0 || j >= COLS) {
                continue;
            }
            count += grid[i][j];
        }
    }
    return count;
}

// Function to update the grid
void update_grid(int grid[ROWS][COLS]) {
    int new_grid[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = count_neighbors(grid, i, j);
            if (grid[i][j]) {
                new_grid[i][j] = (neighbors == 2 || neighbors == 3);
            } else {
                new_grid[i][j] = (neighbors == 3);
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = new_grid[i][j];
        }
    }
}

// Function to print the grid
void print_grid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", grid[i][j] ? 'O' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int grid[ROWS][COLS];

    // Initialize the grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = rand() % 2;
        }
    }

    while (1) {
        print_grid(grid);
        update_grid(grid);
        sleep(1);
    }

    return 0;
}

