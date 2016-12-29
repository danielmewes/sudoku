#ifndef STRATEGIES_ELIMINATECONFLICTS_H
#define STRATEGIES_ELIMINATECONFLICTS_H

class Grid;

// Eliminate candidates that would generate a conflict with an already resolved field
void eliminateConflicts(Grid *grid);

#endif

