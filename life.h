#ifndef LIFE_H

#include <stdint.h>

#define LIFE_H

#define SCREEN_HEIGHT (20)
#define SCREEN_WIDTH (100)

void load_zeros(uint8_t** buffer);
void free_screen_buffer(uint8_t** buffer);
void create_glider(uint8_t** board, size_t x, size_t y);
void create_acorn(uint8_t** board, size_t x, size_t y);
void print_board(uint8_t** board);
void print_square(uint8_t bits);
void next_generation(uint8_t** old_board, uint8_t** new_board);
void next_cell(uint8_t** old_board, uint8_t** new_board, size_t x, size_t y);

#endif
