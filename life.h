#ifndef LIFE_H

#include <stdint.h>

#define LIFE_H

#define SCREEN_HEIGHT (80)
#define SCREEN_WIDTH (250)

#define RIGHT_HALF_BLOCK    "\xE2\x96\x90"
#define LEFT_HALF_BLOCK     "\xE2\x96\x8C"

#define TOP_HALF_BLOCK    "\xE2\x96\x80"
#define BOTTOM_HALF_BLOCK "\xE2\x96\x84"

#define SINGLE_TOP_LEFT     "\xE2\x96\x98"
#define SINGLE_TOP_RIGHT    "\xE2\x96\x9D"
#define SINGLE_BOTTOM_LEFT  "\xE2\x96\x96"
#define SINGLE_BOTTOM_RIGHT "\xE2\x96\x97"

#define L_BLOCK     "\xE2\x96\x99"
#define SEVEN_BLOCK "\xE2\x96\x9C"
#define P_BLOCK     "\xE2\x96\x9B"
#define J_BLOCK     "\xE2\x96\x9F"

#define EMPTY_BLOCK  " "
#define FILLED_BLOCK "\xE2\x96\x88"

#define DIAGONAL_LR_BLOCK "\xE2\x96\x9A"
#define DIAGONAL_RL_BLOCK "\xE2\x96\x9E"

void load_zeros(uint8_t** buffer);
void free_screen_buffer(uint8_t** buffer);
void create_glider(uint8_t** board, size_t x, size_t y);
void create_block(uint8_t** board, size_t x, size_t y);
void create_beehive(uint8_t** board, size_t x, size_t y);
void create_acorn(uint8_t** board, size_t x, size_t y);
void print_board(uint8_t** board);
void print_square(uint8_t bits);
void next_generation(uint8_t** old_board, uint8_t** new_board);
void next_cell(uint8_t** old_board, uint8_t** new_board, size_t x, size_t y);

#endif
