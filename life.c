#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "life.h"

int main(int argc, char** argv) {
    uint8_t** screen1 = (uint8_t**)malloc(sizeof(uint8_t*) * SCREEN_SIZE);
    load_zeros(screen1);

    uint8_t** screen2 = (uint8_t**)malloc(sizeof(uint8_t*) * SCREEN_SIZE);
    load_zeros(screen1);
    printf("loaded zeros...\n");

    create_glider(screen1, 10, 10);
    printf("created glider\n");

    uint8_t** old = screen1;
    uint8_t** new = screen2;
    print_board(old);

    for (int i = 0; i < 1000; ++i) {
        printf("entered loop\n");
        sleep(1);
        next_generation(old, new);
        printf("generated generation\n");
        print_board(new);

        // swap boards...
        uint8_t** tmp = old;
        old = new;
        new = tmp;
    }

    free_screen_buffer(screen1);
    free_screen_buffer(screen2);

    return 0;
}

void free_screen_buffer(uint8_t** buffer) {
    // pass
}

void load_zeros(uint8_t** buffer) {
    for (int i = 0; i < SCREEN_SIZE; ++i) {
        uint8_t* inner_buffer = (uint8_t*)malloc(sizeof(uint8_t) * SCREEN_SIZE);
        buffer[i] = inner_buffer;
    }
}

void create_glider(uint8_t** board, size_t x, size_t y) {
    board[x][y] = 1;
    board[x + 1][y] = 1;
    board[x - 1][y] = 1;
    board[x + 1][y - 1] = 1;
    board[x][y - 2] = 1;
}

void print_board(uint8_t** board) {
    for (size_t i = 0; i < SCREEN_SIZE; ++i) {
        for (size_t j = 0; j < SCREEN_SIZE; ++j) {
            if (board[i][j]) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void next_generation(uint8_t** old_board, uint8_t** new_board) {
    int neighbors;

    // top right
    neighbors = (old_board[0][SCREEN_SIZE - 2])
        + (old_board[1][SCREEN_SIZE - 1])
        + (old_board[1][SCREEN_SIZE - 2]);

    if (old_board[0][SCREEN_SIZE - 1]) {
        new_board[0][SCREEN_SIZE - 1] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[0][SCREEN_SIZE - 1] = neighbors == 3;
    }

    // top left
    neighbors = old_board[0][1] + (old_board[1][0]) + (old_board[1][1]);

    if (old_board[0][0]) {
        new_board[0][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[0][0] = neighbors == 3;
    }

    // bottom left
    neighbors = old_board[SCREEN_SIZE - 1][1]
        + (old_board[SCREEN_SIZE - 2][1])
        + (old_board[SCREEN_SIZE - 2][0]);

    if (old_board[SCREEN_SIZE - 1][0]) {
        new_board[SCREEN_SIZE - 1][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[SCREEN_SIZE - 1][0] = neighbors == 3;
    }

    // bottom right
    neighbors = old_board[SCREEN_SIZE - 2][SCREEN_SIZE - 1]
        + (old_board[SCREEN_SIZE - 2][SCREEN_SIZE - 2])
        + (old_board[SCREEN_SIZE - 1][SCREEN_SIZE - 2]);

    if (old_board[SCREEN_SIZE - 1][0]) {
        new_board[SCREEN_SIZE - 1][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[SCREEN_SIZE - 1][0] = neighbors == 3;
    }
    
    // top row (no corners)
    for (size_t i = 1; i < SCREEN_SIZE - 2; ++i) {
        size_t x = i;
        size_t y = 0;
        neighbors = old_board[x - 1][y]
            + (old_board[x + 1][y])
            + (old_board[x + 1][y + 1])
            + (old_board[x][y + 1])
            + (old_board[x - 1][y + 1]);

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

        neighbors = old_board[x - 1][y]
            + (old_board[x + 1][y])
            + (old_board[x + 1][y + 1])
            + (old_board[x][y + 1])
            + (old_board[x - 1][y + 1]);

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

        neighbors = old_board[x][y - 1]
            + (old_board[x + 1][y - 1])
            + (old_board[x + 1][y])
            + (old_board[x][y + 1])
            + (old_board[x + 1][y + 1]);

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

        neighbors = old_board[x][y - 1]
            + (old_board[x - 1][y - 1])
            + (old_board[x - 1][y])
            + (old_board[x][y + 1])
            + (old_board[x - 1][y + 1]);

        if (old_board[x][y]) {
            new_board[x][y] = 1 - (neighbors < 2) - (neighbors > 3);
        } else {
            new_board[x][y] = neighbors == 3;
        }
    }
    
    // all squares inside
    for (size_t i = 1; i < SCREEN_SIZE - 1; ++i) {
        for (size_t j = 1; i < SCREEN_SIZE - 1; ++j) {
            next_cell(old_board, new_board, i, j);
        }
    }
}

void next_cell(uint8_t** old_board, uint8_t** new_board, size_t x, size_t y) {
    int neighbors = old_board[x - 1][y]
        + (old_board[x][y - 1])
        + (old_board[x - 1][y - 1])
        + (old_board[x + 1][y])
        + (old_board[x + 1][y + 1])
        + (old_board[x][y + 1])
        + (old_board[x - 1][y + 1])
        + (old_board[x + 1][y - 1]);

    if (old_board[x][y]) {
        new_board[x][y] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[x][y] = neighbors == 3;
    }
}
