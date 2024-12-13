#include "colony.hpp"
#include "parameters.hpp"


// colony constructor function
Colony::Colony(Parameters const &params) :
    cells{params.min_cells_colony, Cell(params)} // initialize each colony with given number of cells
{
    // initialize division time distribution
    for (auto cell_iter = cells.begin();
            cell_iter != cells. end();
            ++cell_iter)
    {
        division_times.push_back(cell_iter->.division);
    }
}
