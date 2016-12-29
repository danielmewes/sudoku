#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <functional>
#include <assert.h>
#include <stdlib.h>

#include "field.h"
#include "grid.h"
#include "solver.h"

void readSudoku(const std::string &filename, Grid *grid_out) {
    std::ifstream file(filename.c_str());
    if (!file.good()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        exit(-1);
    }
    assert(file.good());
    size_t row = 0;
    size_t col = 0;
    while (!file.eof() && row < 9) {
        char ch;
        file.get(ch);
        switch (ch) {
            case '\r':
            case '\n':
                assert(col == 0 || col == 9);
                // if col is 0, this might have been a separator line (-----)
                // or we got DOS line endings.
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
                    std::cerr << "Unexpected character '" << ch << "\n";
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
        if ((row + 1) % 3 == 0 && row < 8) {
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
    if (argc != 2) {
        std::cerr << "Wrong number of arguments. Please call: \n" << argv[0] << " <filename.ss>\n";
        exit(-1);
    }
    assert(argc >= 2);
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

