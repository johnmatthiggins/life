#include <stdint.h>
#include <string.h>

#include "life.h"


// store two states for the game screen...
uint8_t screen1[SCREEN_SIZE * SCREEN_SIZE];
uint8_t screen2[SCREEN_SIZE * SCREEN_SIZE];

int main(int argc, char** argv) {
    memset(screen1, 0, SCREEN_SIZE * SCREEN_SIZE);
    memset(screen2, 0, SCREEN_SIZE * SCREEN_SIZE);

    return 0;
}

void next_generation(uint8_t* old_board, uint8_t* new_board) {
    // top right
    // top left
    // bottom left
    // bottom right
    
    // top row (no corners)
    // bottom row (no corners)
    // left row (no corners)
    // right row (no corners)
    
    // all squares inside
    for (size_t i = 1; i < SCREEN_SIZE - 1; i++) {
        for (size_t j = 1; i < SCREEN_SIZE - 1; j++) {
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
    }
}
