#include "solver.h"

#include <iostream>
#include <assert.h>

#include "field.h"
#include "grid.h"
#include "strategies/eliminateConflicts.h"
#include "strategies/resolveRequired.h"
#include "strategies/guessOne.h"


void solveDeterministic(Grid *grid) {
    eliminateConflicts(grid);
    resolveRequired(grid);
}

void solveDeterministicUntilStuck(Grid *grid) {
    Grid oldGrid;
    do {
        oldGrid = *grid;
        solveDeterministic(grid);
        std::cout << ".";
    } while (oldGrid != *grid);
}

void solve(Grid *grid, int depth) {
    const int MAX_DEPTH = 16;
    if (depth > MAX_DEPTH) {
        std::cerr << "Recursion depth limit hit.\n";
    }
    if (depth > MAX_DEPTH) {
        return;
    }
    solveDeterministicUntilStuck(grid);
    std::cout << "\n";
    if (!grid->isResolved() && !grid->hasConflict()) {
        Grid branch = *grid;
        Guess guess = guessOne(&branch);
        std::cout << "Guessing " << guess.row + 1 << "," << guess.col + 1 << "=" << guess.value << " (depth=" << depth << ")\n";
        if (guess.value != 0) {
            // Continue recursively, assuming the guess
            solve(&branch, depth + 1);
            bool hasConflict = branch.hasConflict();
            if (!hasConflict && branch.isResolved()) {
                // The guess was succesful!
                *grid = branch;
            } else if (hasConflict) {
                // Definitely a wrong guess. Remove the candidate. Then try again.
                std::cout << "Made a wrong guess, but learnt something from it.\n";
                (*grid)[guess.row][guess.col].eraseCandidate(guess.value);
                return solve(grid, depth);
            }
        } else {
            std::cout << "Nothing left to guess. Unsolvable?\n";
        }
    }
}

void solve(Grid *grid) {
    solve(grid, 0);
}
