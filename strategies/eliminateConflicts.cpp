#include "eliminateConflicts.h"

#include <functional>
#include <assert.h>

#include "../field.h"
#include "../grid.h"

class CollectResolvedHelper {
public:
    void operator()(Field *field) {
        if (field->isResolved()) {
            result.insert(field->getResolved());
        }
    }

    const std::set<int> &getResult() const {
        return result;
    }

private:
    std::set<int> result;
};

void eliminateConflicts(const std::function<void(size_t cell, const std::function<void(Field *)> &f)> &iterate) {
    for (size_t i = 0; i < 9; ++i) {
        CollectResolvedHelper collect;
        iterate(i, [&](Field *field) {
            collect(field);
        });
        iterate(i, [&](Field *field) {
            if (field->isResolved()) {
                return;
            }
            for (int usedCandidate : collect.getResult()) {
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
