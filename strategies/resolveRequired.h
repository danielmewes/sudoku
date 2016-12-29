#ifndef STRATEGIES_RESOLVEREQUIRED_H
#define STRATEGIES_RESOLVEREQUIRED_H

class Grid;

// Resolve fields for which we *must* pick a certain candidate to complete a row / column / cell
void resolveRequired(Grid *grid);

#endif

