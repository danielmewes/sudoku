#ifndef STRATEGIES_GUESSONE_H
#define STRATEGIES_GUESSONE_H

#include <cstddef>

class Grid;

struct Guess {
    size_t row;
    size_t col;
    int value;
};

// Guess a value
Guess guessOne(Grid *grid);

#endif

