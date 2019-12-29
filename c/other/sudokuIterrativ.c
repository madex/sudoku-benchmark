#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

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

static inline bool rule_valid(uint8_t *board, uint8_t *rule) {
    unsigned short flags[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (unsigned char i = 9*9; i; i--, board++, rule++) {
        if (*board != 0) {
            unsigned short mask = (1 << *board);
            if (flags[*rule] & mask) {
                return false;
            }
            flags[*rule] |= mask;
        }
    }
    return true;
}

static inline bool check(uint8_t *board, uint8_t **rules) {
    while (*rules) { // check all rules
        if (!rule_valid(board, *rules++)) {
            return false;
        }
    }
    return true;
}

static inline void find_next_free(uint8_t *board, uint8_t *field) {
    for (; *field < 9*9; (*field)++) {
        if (board[*field] == 0) {
            break;
        }
    }
}

static bool sudoku_try_set_field(uint8_t *board, uint8_t **rules) {
    uint8_t path[9*9];
    memset(path, 0, sizeof path);
    uint8_t *pathPtr = path;
    find_next_free(board, pathPtr);
    while (1) { // find field_no of the next unset field
        if (*pathPtr >= 9*9) {
            return true; // solved
        } else {
            while (board[*pathPtr] < 9) {
                board[*pathPtr]++;
                if (check(board, rules)) {
                    uint8_t help = *pathPtr;
                    pathPtr++;
                    if ((pathPtr - path) < sizeof(path)) {
                        *pathPtr = help;
                        find_next_free(board, pathPtr);
                    }
                    break;
                }
            }
            if (board[*pathPtr] >= 9) {
                board[*pathPtr] = 0;
                if (pathPtr > path) {
                    pathPtr--;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

static void print_board(uint8_t *board) {
    uint8_t j = 0, l = 0, i;
    for (i = 9*9; i; i--, board++) {
        if (*board == 0) { printf(" _"); }
        else printf(" %d", *board);
        if ((j % 3) == 2) { printf(" "); }
        if (++j == 9) {
            if ((l++ % 3) == 2) { printf("\n"); }
            j = 0;
            printf("\n");
        }
    }
}

int main() {
    // don't miss 0 endmarker in definition of *rules[]
    uint8_t *rules[] = {rule_rows, rule_colums, rule_basic_blocks, 0}; 
    uint8_t *board = quiz;
    double time;
    printf("solve following sudoko:\n");
    print_board(board);
    time = clock();
    if (sudoku_try_set_field(board, rules)) {
        printf("found solution in %f ns\n", clock() - time);
        print_board(board);
    } else {
        printf("no solition found\n");
    }
    return 0;
}
