#include "colony.hpp"
#include "parameters.hpp"


Colony::Colony(Parameters const &params) :
    Cells{params.min_cells_colony, Cell(params)}
{}
