#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 60
#define COLS 75
#define CELL_SIZE 20

int grid[ROWS * COLS];
int new_grid[ROWS * COLS];

// Function to count the number of live neighbors
int count_neighbors(int row, int col)
{
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) 
    {
        for (int j = col - 1; j <= col + 1; j++) 
        {
            if (i == row && j == col)
            {
                continue;
            }
            if (i < 0 || i >= ROWS || j < 0 || j >= COLS) 
            {
                continue;
            }
            count += grid[i * COLS + j];
        }
    }
    return count;
}

// Function to update the grid
void update_grid()
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            int neighbors = count_neighbors(i, j);
            if (grid[i * COLS + j])
            {
                new_grid[i * COLS + j] = (neighbors == 2 || neighbors == 3);
            } 
            else 
            {
                new_grid[i * COLS + j] = (neighbors == 3);
            }
        }
    }
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            grid[i * COLS + j] = new_grid[i * COLS + j];
        }
    }
}

int main()
{
    // Initialize the grid
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            grid[i * COLS + j] = rand() % 2;
        }
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, COLS * CELL_SIZE, ROWS * CELL_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL) 
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Main loop
    while (1)
    {
        // Handle events
        SDL_Event e;
        if (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                break;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Draw the cells
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                if (grid[i * COLS + j]) 
                {
                    SDL_Rect rect = {j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }

        // Update the grid
        update_grid();

        // Update the screen
        SDL_RenderPresent(renderer);

        // Sleep for a short period
        SDL_Delay(100);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
