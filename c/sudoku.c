#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

uint8_t rule_rows[9*9] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7,
    8, 8, 8, 8, 8, 8, 8, 8, 8
};
uint8_t rule_colums[9*9] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8,
    0, 1, 2, 3, 4, 5, 6, 7, 8
};
uint8_t rule_basic_blocks[9*9] = {
    0, 0, 0,  1, 1, 1,  2, 2, 2,
    0, 0, 0,  1, 1, 1,  2, 2, 2,
    0, 0, 0,  1, 1, 1,  2, 2, 2,

    3, 3, 3,  4, 4, 4,  5, 5, 5,
    3, 3, 3,  4, 4, 4,  5, 5, 5,
    3, 3, 3,  4, 4, 4,  5, 5, 5,

    6, 6, 6,  7, 7, 7,  8, 8, 8,
    6, 6, 6,  7, 7, 7,  8, 8, 8,
    6, 6, 6,  7, 7, 7,  8, 8, 8
};

uint8_t quiz[9*9] = { //  http://www.kubieziel.de/blog/archives/684-schwerstes-Sudoku.html
    1, 0, 0,  0, 0, 7,  0, 9, 0,
    0, 3, 0,  0, 2, 0,  0, 0, 8,
    0, 0, 9,  6, 0, 0,  5, 0, 0,
    0, 0, 5,  3, 0, 0,  9, 0, 0,
    0, 1, 0,  0, 8, 0,  0, 0, 2,
    6, 0, 0,  0, 0, 4,  0, 0, 0,
    3, 0, 0,  0, 0, 0,  0, 1, 0,
    0, 4, 0,  0, 0, 0,  0, 0, 7,
    0, 0, 7,  0, 0, 0,  3, 0, 0,
};

uint8_t quiz2[9*9] = { // (standart rules)
    0, 0, 2,  6, 0, 8,  1, 0, 0,
    0, 0, 0,  1, 4, 3,  0, 0, 0,
    0, 3, 0,  0, 0, 0,  0, 6, 0,
    0, 9, 7,  8, 0, 4,  5, 2, 0,
    1, 0, 0,  0, 0, 0,  0, 0, 8,
    0, 8, 5,  7, 0, 6,  9, 1, 0,
    0, 2, 0,  0, 0, 0,  0, 3, 0,
    0, 0, 0,  2, 7, 9,  0, 0, 0,
    0, 0, 4,  3, 0, 1,  7, 0, 0,
};
static void print_board(uint8_t *board);
static inline bool rule_valid(uint8_t *board, uint8_t *rule, uint8_t *sets) {
    uint32_t flags[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t i;
    for (i = 0; i < 9*9; i++, board++) {
        if (*board == 0) continue;
        uint32_t mask = (1 << *board);
        uint8_t r = rule[i];
        if (flags[r] & mask) {
            return false;
        }
        flags[r] |= mask;
    }
    for (i = 0; i < 9*9; i++) {
        sets[i] |= flags[rule[i]];
    }
    return true;
}

static bool check(uint8_t *board, uint8_t **rules, uint8_t *sets) {
    while (*rules) { // check all rules
        if (!rule_valid(board, *rules++, sets)) {
            return false;
        }
    }
    return true;
}

static bool sudoku_try_set_field(uint8_t field_no, uint8_t *board, 
                                 uint8_t **rules, uint8_t *sets) {
    uint32_t i;
    while (1) { // find field_no of the next unset field
        if (field_no >= 9*9) {
            return true; // solved
        }
        if (board[field_no] == 0) {
            break;
        }
        field_no++;	
    }
    for (i = 1; i < 10; i++) {
        if (((1 << i) & sets[field_no]) == 0) {
            uint8_t newSets[81];
            memcpy((void*) newSets, (void*)sets, 81); 
            board[field_no] = i;
            if (check(board, rules, newSets)) {
                if (sudoku_try_set_field(field_no+1, board, rules, newSets)) {
                    return true;
                }
            }
        }
    }
    board[field_no] = 0;
    return false;
}

static void print_board(uint8_t *board) {
    for (uint32_t i = 0; i < 9*9; i++, board++) {
        if (*board == 0) { 
            printf(" _"); 
        } else { 
            printf(" %d", *board);
        }
        if ((i %  3) ==  2) { printf(" "); }
        if ((i %  9) ==  8) { printf("\n"); }
        if ((i % 27) == 26) { printf("\n"); }
    }
}
uint8_t sudoku_solve(uint8_t *board, uint8_t **rules) {
    uint8_t sets[81];
    memset(sets, 0, 81);
    return sudoku_try_set_field(0, board, rules, sets);
}
int main() {
    // don�t miss 0 endmarker in definition of *rules[]
    uint8_t *rules[] = {rule_rows, rule_colums, rule_basic_blocks, 0}; 
    uint8_t *board = quiz;
    double time;
    printf("solve following sudoko:\n");
    print_board(board);
    time = clock();
    if (sudoku_solve(board, rules)) {
        printf("found solution in %f us\n", clock() - time);
        print_board(board);
    } else {
        printf("no solition found\n");
    }
    return 0;
}
