#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "life.h"

int main(int argc, char** argv) {
    uint8_t** screen1 = (uint8_t**)malloc(sizeof(uint8_t*) * SCREEN_WIDTH);
    load_zeros(screen1);

    uint8_t** screen2 = (uint8_t**)malloc(sizeof(uint8_t*) * SCREEN_WIDTH);
    load_zeros(screen2);

    create_glider(screen1, 20, 20);

    uint8_t** old = screen1;
    uint8_t** new = screen2;

    print_board_ascii(old);

    for (;;) {
        usleep(100000);
        next_generation(old, new);
        print_board_ascii(new);

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
    for (size_t i = 0; i < SCREEN_WIDTH; ++i) {
        free(buffer[i]);
    }

    free(buffer);
}

void load_zeros(uint8_t** buffer) {
    for (int i = 0; i < SCREEN_WIDTH; ++i) {
        uint8_t* inner_buffer = (uint8_t*)malloc(sizeof(uint8_t) * SCREEN_HEIGHT);
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

void create_block(uint8_t** board, size_t x, size_t y) {
    board[x][y] = 1;
    board[x + 1][y] = 1;
    board[x + 1][y + 1] = 1;
    board[x][y + 1] = 1;
}

void create_beehive(uint8_t** board, size_t x, size_t y) {
    board[x][y - 1] = 1;
    board[x + 1][y - 1] = 1;
    board[x - 1][y] = 1;
    board[x + 2][y] = 1;

    board[x][y + 1] = 1;
    board[x + 1][y + 1] = 1;
}

void create_acorn(uint8_t** board, size_t x, size_t y) {
    board[x + 1][y] = 1;
    board[x + 2][y] = 1;
    board[x + 3][y] = 1;

    board[x][y - 1] = 1;
    
    board[x - 2][y] = 1;
    board[x - 3][y] = 1;

    board[x - 2][y - 2] = 1;
}

void print_board_ascii(uint8_t** board) {
    clear_screen();
    printf("\xE2\x95\x94");
    for (size_t i = 1; i < SCREEN_WIDTH + 1; ++i) {
        printf("\xE2\x95\x90");
    }
    printf("\xE2\x95\x97\n");

    for (size_t i = 0; i < SCREEN_HEIGHT; i++) {
        printf("\xE2\x95\x91");
        for (size_t j = 0; j < SCREEN_WIDTH; j++) {
            if (board[j][i]) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\xE2\x95\x91\n");
    }

    printf("\xE2\x95\x9A");
    for (size_t i = 1; i < SCREEN_WIDTH + 1; ++i) {
        printf("\xE2\x95\x90");
    }
    printf("\xE2\x95\x9D\n");
}

void print_board(uint8_t** board) {
    for (size_t i = 0; i < (SCREEN_WIDTH / 2) + 2; ++i) {
        printf("X");
    }
    printf("\n");

    for (size_t i = 0; i < SCREEN_HEIGHT; i += 2) {
        printf("X");
        for (size_t j = 0; j < SCREEN_WIDTH; j += 2) {
            uint8_t bits = board[j][i] << 3
                | board[j + 1][i] << 2
                | board[j][i + 1] << 1
                | board[j + 1][i + 1] << 0;

            print_square(bits);
        }
        printf("X\n");
    }

    for (size_t i = 0; i < (SCREEN_WIDTH / 2) + 2; ++i) {
        printf("X");
    }
    printf("\n");
}

void print_square(uint8_t bits) {
    switch (bits) {
        case 0b1111:
            // full block
            printf("%s", FILLED_BLOCK);
            break;
        case 0b0000:
            printf("%s", EMPTY_BLOCK);
            break;
        case 0b1000:
            printf("%s", SINGLE_TOP_LEFT);
            break;
        case 0b0100:
            printf("%s", SINGLE_TOP_RIGHT);
            break;
        case 0b0010:
            printf("%s", SINGLE_BOTTOM_LEFT);
            break;
        case 0b0001:
            printf("%s", SINGLE_BOTTOM_RIGHT);
            break;
        case 0b1100:
            printf("%s", TOP_HALF_BLOCK);
            break;
        case 0b0011:
            printf("%s", BOTTOM_HALF_BLOCK);
            break;
        case 0b1001:
            printf("%s", DIAGONAL_RL_BLOCK);
            break;
        case 0b0110:
            printf("%s", DIAGONAL_LR_BLOCK);
            break;
        case 0b1010:
            printf("%s", LEFT_HALF_BLOCK);
            break;
        case 0b0101:
            printf("%s", RIGHT_HALF_BLOCK);
            break;
        case 0b1101:
            printf("%s", SEVEN_BLOCK);
            break;
        case 0b1011:
            printf("%s", L_BLOCK);
            break;
        case 0b1110:
            printf("%s", P_BLOCK);
            break;
        case 0b0111:
            printf("%s", J_BLOCK);
            break;
        default:
            printf(" ");
            break;
    }
}

void next_generation(uint8_t** old_board, uint8_t** new_board) {
    int neighbors;

    // top right
    neighbors = old_board[0][SCREEN_HEIGHT - 2]
        + old_board[1][SCREEN_HEIGHT - 1]
        + old_board[1][SCREEN_HEIGHT - 2];

    if (old_board[0][SCREEN_HEIGHT - 1]) {
        new_board[0][SCREEN_HEIGHT - 1] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[0][SCREEN_HEIGHT - 1] = neighbors == 3;
    }

    // top left
    neighbors = old_board[0][1] + (old_board[1][0]) + (old_board[1][1]);

    if (old_board[0][0]) {
        new_board[0][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[0][0] = neighbors == 3;
    }

    // bottom left
    neighbors = old_board[SCREEN_WIDTH - 1][1]
        + old_board[SCREEN_WIDTH - 2][1]
        + old_board[SCREEN_WIDTH - 2][0];

    if (old_board[SCREEN_WIDTH - 1][0]) {
        new_board[SCREEN_WIDTH - 1][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[SCREEN_WIDTH - 1][0] = neighbors == 3;
    }

    // bottom right
    neighbors = old_board[SCREEN_WIDTH - 2][SCREEN_HEIGHT - 1]
        + old_board[SCREEN_WIDTH - 2][SCREEN_HEIGHT - 2]
        + old_board[SCREEN_WIDTH - 1][SCREEN_HEIGHT - 2];

    if (old_board[SCREEN_WIDTH - 1][0]) {
        new_board[SCREEN_WIDTH - 1][0] = 1 - (neighbors < 2) - (neighbors > 3);
    } else {
        new_board[SCREEN_WIDTH - 1][0] = neighbors == 3;
    }
    
    // top row (no corners)
    for (size_t i = 1; i < SCREEN_WIDTH - 1; ++i) {
        size_t x = i;
        size_t y = 0;
        neighbors = old_board[x - 1][y]
            + old_board[x + 1][y]
            + old_board[x + 1][y + 1]
            + old_board[x][y + 1]
            + old_board[x - 1][y + 1];

        if (old_board[x][y]) {
            new_board[x][y] = 1 - (neighbors < 2) - (neighbors > 3);
        } else {
            new_board[x][y] = neighbors == 3;
        }
    }

    // bottom row (no corners)
    for (size_t i = 1; i < SCREEN_WIDTH - 1; ++i) {
        size_t x = i;
        size_t y = SCREEN_HEIGHT - 1;

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
    for (size_t i = 1; i < SCREEN_HEIGHT - 1; ++i) {
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
    for (size_t i = 1; i < SCREEN_HEIGHT - 1; ++i) {
        size_t x = SCREEN_WIDTH - 1;
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
    for (size_t i = 1; i < SCREEN_WIDTH - 1; ++i) {
        for (size_t j = 1; j < SCREEN_HEIGHT - 1; ++j) {
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

void clear_screen() {
    printf("\e[1;1H\e[2J");
}
