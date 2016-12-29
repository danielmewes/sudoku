#ifndef GRID_H
#define GRID_H

#include <functional>
#include <vector>

#include "field.h"

class Grid {
public:
    Grid();

    std::vector<Field> &operator[](size_t row);
    const std::vector<Field> &operator[](size_t row) const;
    
    bool operator==(const Grid &other) const;
    bool operator!=(const Grid &other) const;

    bool hasConflict();
    
    bool isResolved() const;
    
    void forEachInRow(size_t row, const std::function<void(Field *)> &f);
    void forEachInCol(size_t col, const std::function<void(Field *)> &f);
    // cell 0-8
    void forEachInCell(size_t cell, const std::function<void(Field *)> &f);

private:
    std::vector<std::vector<Field> > grid;
};

#endif

