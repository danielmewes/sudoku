#include "guessOne.h"

#include <assert.h>

#include "../field.h"
#include "../grid.h"

Guess guessOne(Grid *grid) {
    // Pick the field with the smallest number of candidates for our guess.
    Guess guess{0, 0, 0};
    size_t bestNumCandidates = 0;
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            const Field &field = (*grid)[row][col];
            if (field.isResolved() || field.hasConflict()) {
                continue;
            }
            size_t numCandidates = field.getCandidates().size();
            if (bestNumCandidates == 0 || numCandidates < bestNumCandidates) {
                bestNumCandidates = numCandidates;
                guess = Guess{row, col, *field.getCandidates().begin()};
            }
        }
    }
    if (bestNumCandidates != 0) {
        // Set the guess in grid
        (*grid)[guess.row][guess.col].setResolved(guess.value);
    }
    
    return guess;
}
