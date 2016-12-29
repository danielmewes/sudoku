#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <functional>
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

void solve(Grid *grid, int depth = 0) {
    const int MAX_DEPTH = 10;
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
        std::cout << "Guessing " << guess.row << "," << guess.col << "=" << guess.value << " (depth=" << depth << ")\n";
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

void readSudoku(const std::string &filename, Grid *grid_out) {
    std::ifstream file(filename.c_str());
    assert(file.good());
    size_t row = 0;
    size_t col = 0;
    while (!file.eof() && row < 9) {
        char ch;
        file.get(ch);
        switch (ch) {
            case '\n':
                assert(col == 0 || col == 9);
                // So we skip over seperator lines
                if (col == 9) {
                    ++row;
                }
                col = 0;
                break;
            case '.':
                ++col;
                break;
            case '|':
                break;
            case '-':
                break;
            default:
                if (ch > '9' || ch < '1') {
                    std::cerr << "Unexpected character '" << ch << "' on line " << row + 1 << "\n";
                }
                assert('1' <= ch && ch <= '9');
                (*grid_out)[row][col].setResolved(static_cast<int>(ch - '0'));
                ++col;
                break;
        }
    }
    assert(col == 0);
    assert(row == 9);
}

void printSudoku(const Grid &grid, const std::function<char(const Field &)> &formatField) {
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            std::cout << formatField(grid[row][col]);
            if ((col + 1) % 3 == 0 && col < 8) {
                std::cout << '|';
            }
        }
        std::cout << "\n";
        if ((row + 1) % 3 == 0) {
            std::cout << "-----------\n";
        }
    }
}

char formatFieldResolved(const Field &field) {
    if (field.isResolved()) {
        return static_cast<char>('0' + field.getResolved());
    } else {
        return '.';
    }
}

// Useful for debugging
char formatFieldCandidate(int value, const Field &field) {
    if (field.getCandidates().count(value) == 1) {
        return '*';
    } else {
        return ' ';
    }
}

int main(int argc, char **argv) {
    assert(argc == 2);
    std::string filename = argv[1];

    Grid grid;
    readSudoku(filename, &grid);
    std::cout << "Input:\n";
    printSudoku(grid, &formatFieldResolved);
    std::cout << "\n";
    assert(!grid.hasConflict());
    
    std::cout << "Solving:\n";
    solve(&grid);
    assert(!grid.hasConflict());
    std::cout << "\nResult:\n";
    printSudoku(grid, &formatFieldResolved);
    
    if (grid.isResolved()) {
        std::cout << "\nSolved it :)\n";
        return 0;
    } else {
        return 1;
    }
}

