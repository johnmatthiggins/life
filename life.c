#include <unistd.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "life.h"


// store two states for the game screen...
uint8_t screen1[SCREEN_SIZE * SCREEN_SIZE];
uint8_t screen2[SCREEN_SIZE * SCREEN_SIZE];

int main(int argc, char** argv) {
    memset(screen1, 0, SCREEN_SIZE * SCREEN_SIZE);
    memset(screen2, 0, SCREEN_SIZE * SCREEN_SIZE);

    create_glider(screen1, 10, 10);

    uint8_t* old = screen1;
    uint8_t* new = screen2;

    for (int i = 0; i < 1000; ++i) {
        sleep(1);
        next_generation(old, new);
        print_board(new);

        // swap boards...
        uint8_t* tmp = old;
        old = new;
        new = tmp;
    }

    return 0;
}

void create_glider(uint8_t* board, size_t x, size_t y) {
    board[x][y] = 1;
    board[x + 1][y] = 1;
    board[x - 1][y] = 1;
    board[x + 1][y - 1] = 1;
    board[x][y - 2] = 1;
}

void print_board(uint8_t* board) {
    for (size_t i = 0; i < SCREEN_SIZE; ++i) {
        for (size_t j = 0; j < SCREEN_SIZE; ++j) {
            if (board[i][j]) {
                printf("@");
            }
        }
        printf("\n");
    }
}

void next_generation(uint8_t* old_board, uint8_t* new_board) {
    int adjacent;
    int neighbors;

    // top right
    adjacent = (old_board[0][SCREEN_SIZE - 2])
        | (old_board[1][SCREEN_SIZE - 1] << 1)
        | (old_board[1][SCREEN_SIZE - 2] << 2);

    neighbors = __builtin__popcount(adjacent);

    if (old_board[0][SCREEN_SIZE - 1]) {
        new_board[0][SCREEN_SIZE - 1] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[0][SCREEN_SIZE - 1] = neighbors == 3;
    }

    // top left
    adjacent = old_board[0][1]
        | (old_board[1][0] << 1) | (old_board[1][1] << 2);

    neighbors = __builtin__popcount(adjacent);

    if (old_board[0][0]) {
        new_board[0][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[0][0] = neighbors == 3;
    }

    // bottom left
    adjacent = old_board[SCREEN_SIZE - 1][1]
        | (old_board[SCREEN_SIZE - 2][1] << 1)
        | (old_board[SCREEN_SIZE - 2][0] << 2);

    neighbors = __builtin__popcount(adjacent);

    if (old_board[SCREEN_SIZE - 1][0]) {
        new_board[SCREEN_SIZE - 1][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[SCREEN_SIZE - 1][0] = neighbors == 3;
    }

    // bottom right
    adjacent = old_board[SCREEN_SIZE - 2][SCREEN_SIZE - 1]
        | (old_board[SCREEN_SIZE - 2][SCREEN_SIZE - 2] << 1)
        | (old_board[SCREEN_SIZE - 1][SCREEN_SIZE - 2] << 2);

    neighbors = __builtin__popcount(adjacent);

    if (old_board[SCREEN_SIZE - 1][0]) {
        new_board[SCREEN_SIZE - 1][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[SCREEN_SIZE - 1][0] = neighbors == 3;
    }
    
    // top row (no corners)
    for (size_t i = 1; i < SCREEN_SIZE - 2; ++i) {
        size_t x = i;
        size_t y = 0;
        adjacent = old_board[x - 1][y]
            | (old_board[x + 1][y] << 1)
            | (old_board[x + 1][y + 1] << 2)
            | (old_board[x][y + 1] << 3)
            | (old_board[x - 1][y + 1] << 4);

        neighbors = __builtin__popcount(adjacent);

        if (old_board[x][y]) {
            new_board[x][y] = 1 - (neighbors < 2) - (neighbors > 3);
        } else {
            new_board[x][y] = neighbors == 3;
        }
    }

    // bottom row (no corners)
    for (size_t i = 1; i < SCREEN_SIZE - 2; ++i) {
        size_t x = i;
        size_t y = SCREEN_SIZE - 1;

        adjacent = old_board[x - 1][y]
            | (old_board[x + 1][y] << 1)
            | (old_board[x + 1][y + 1] << 2)
            | (old_board[x][y + 1] << 3)
            | (old_board[x - 1][y + 1] << 4);

        neighbors = __builtin__popcount(adjacent);

        if (old_board[x][y]) {
            new_board[x][y] = 1 - (neighbors < 2) - (neighbors > 3);
        } else {
            new_board[x][y] = neighbors == 3;
        }
    }

    // left row (no corners)
    for (size_t i = 1; i < SCREEN_SIZE - 2; ++i) {
        size_t x = 0;
        size_t y = i;

        adjacent = old_board[x][y - 1]
            | (old_board[x + 1][y - 1] << 1)
            | (old_board[x + 1][y] << 2)
            | (old_board[x][y + 1] << 3)
            | (old_board[x + 1][y + 1] << 4);

        neighbors = __builtin__popcount(adjacent);

        if (old_board[x][y]) {
            new_board[x][y] = 1 - (neighbors < 2) - (neighbors > 3);
        } else {
            new_board[x][y] = neighbors == 3;
        }
    }

    // right row (no corners)
    for (size_t i = 1; i < SCREEN_SIZE - 2; ++i) {
        size_t x = SCREEN_SIZE - 1;
        size_t y = i;

        adjacent = old_board[x][y - 1]
            | (old_board[x - 1][y - 1] << 1)
            | (old_board[x - 1][y] << 2)
            | (old_board[x][y + 1] << 3)
            | (old_board[x - 1][y + 1] << 4);

        neighbors = __builtin__popcount(adjacent);

        if (old_board[x][y]) {
            new_board[x][y] = 1 - (neighbors < 2) - (neighbors > 3);
        } else {
            new_board[x][y] = neighbors == 3;
        }
    }
    
    // all squares inside
    for (size_t i = 1; i < SCREEN_SIZE - 1; ++i) {
        for (size_t j = 1; i < SCREEN_SIZE - 1; ++j) {
            next_cell(old_board, new_board, x, y);
        }
    }
}

void next_cell(uint8_t* old_board, uint8_t* new_board, size_t x, size_t y) {
    int adjacent = old_board[i - 1][j]
        | (old_board[i][j - 1] << 1)
        | (old_board[i - 1][j - 1] << 2)
        | (old_board[i + 1][j] << 3)
        | (old_board[i + 1][j + 1] << 4)
        | (old_board[i][j + 1] << 5)
        | (old_board[i - 1][j + 1] << 6)
        | (old_board[i + 1][j - 1] << 7);

    int neighbors = __builtin__popcount(adjacent);

    if (old_board[i][j]) {
        new_board[i][j] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[i][j] = neighbors == 3;
    }
}
