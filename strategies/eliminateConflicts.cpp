#include "eliminateConflicts.h"

#include <functional>
#include <assert.h>

#include "../field.h"
#include "../grid.h"


void eliminateConflicts(const std::function<void(size_t cell, const std::function<void(Field *)> &f)> &iterate) {
    for (size_t i = 0; i < 9; ++i) {
        std::set<int> collected;
        iterate(i, [&](Field *field) {
            if (field->isResolved()) {
                collected.insert(field->getResolved());
            }
        });
        iterate(i, [&](Field *field) {
            if (field->isResolved()) {
                return;
            }
            for (int usedCandidate : collected) {
                field->eraseCandidate(usedCandidate);
            }
        });
    }
}

void eliminateConflicts(Grid *grid) {
    using namespace std::placeholders;
    eliminateConflicts(std::bind(&Grid::forEachInRow, grid, _1, _2));
    eliminateConflicts(std::bind(&Grid::forEachInCol, grid, _1, _2));
    eliminateConflicts(std::bind(&Grid::forEachInCell, grid, _1, _2));
}
