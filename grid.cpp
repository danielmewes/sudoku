#include "grid.h"

#include <assert.h>

Grid::Grid() {
    grid.resize(9, std::vector<Field>(9, Field()) );
}

std::vector<Field> &Grid::operator[](size_t row) {
    return grid[row];
}

const std::vector<Field> &Grid::operator[](size_t row) const {
    return grid[row];
}

bool Grid::operator==(const Grid &other) const {
    return grid == other.grid;
}

bool Grid::operator!=(const Grid &other) const {
    return grid != other.grid;
}

bool Grid::hasConflict() {
    bool hasConflict = false;
    std::set<int> usedValues;
    auto checkConflict = [&](Field *field) {
        if (field->hasConflict()) {
            hasConflict = true;
        } else if (field->isResolved()) {
            if (usedValues.count(field->getResolved()) > 0) {
                hasConflict = true;
            } else {
                usedValues.insert(field->getResolved());
            }
        }
    };
    for (size_t i = 0; i < 9; ++i) {
        forEachInRow(i, checkConflict);
        usedValues.clear();
        forEachInCol(i, checkConflict);
        usedValues.clear();
        forEachInCell(i, checkConflict);
        usedValues.clear();
        if (hasConflict) {
            break;
        }
    }
    return hasConflict;
}

bool Grid::isResolved() const {
    for (const auto &row : grid) {
        for (const auto &field : row) {
            if (!field.isResolved()) {
                return false;
            }
        }
    }
    return true;
}

void Grid::forEachInRow(size_t row, const std::function<void(Field *)> &f) {
    for (auto &field : grid[row]) {
        f(&field);
    }
}

void Grid::forEachInCol(size_t col, const std::function<void(Field *)> &f) {
    for (auto &row : grid) {
        Field &field = row[col];
        f(&field);
    }
}

void Grid::forEachInCell(size_t cell, const std::function<void(Field *)> &f) {
    size_t minRow = (cell / 3) * 3;
    size_t maxRow = minRow + 3;
    size_t minCol = (cell % 3) * 3;
    size_t maxCol = minCol + 3;
    for (size_t rowIdx = minRow; rowIdx < maxRow; ++rowIdx) {
        for (size_t colIdx = minCol; colIdx < maxCol; ++colIdx) {
            Field &field = grid[rowIdx][colIdx];
            f(&field);
        }
    }
}
