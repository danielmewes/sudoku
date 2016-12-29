#include "eliminateConflicts.h"

#include <functional>
#include <assert.h>

#include "../field.h"
#include "../grid.h"

void resolveRequired(const std::function<void(size_t cell, const std::function<void(Field *)> &f)> &iterate) {
    for (size_t i = 0; i < 9; ++i) {
        for (int value = 1; value <= 9; ++value) {
            Field *fieldWithCandidate = nullptr;
            bool unique = true;
            iterate(i, [&](Field *field) {
                if (field->getCandidates().count(value) == 1) {
                    if (fieldWithCandidate == nullptr) {
                        fieldWithCandidate = field;
                    } else {
                        unique = false;
                    }
                }
            });
            if (fieldWithCandidate != nullptr && unique) {
                fieldWithCandidate->setResolved(value);
            }
        }
    }
}

void resolveRequired(Grid *grid) {
    using namespace std::placeholders;
    resolveRequired(std::bind(&Grid::forEachInRow, grid, _1, _2));
    resolveRequired(std::bind(&Grid::forEachInCol, grid, _1, _2));
    resolveRequired(std::bind(&Grid::forEachInCell, grid, _1, _2));
}
