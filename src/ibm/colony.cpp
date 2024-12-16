#include <cassert>
#include <random>
#include <iostream>
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
        assert(cell_iter->division > 0.0);
        division_rates.push_back(1.0/cell_iter->division);
    }
}

// remove a random cell from colony
void Colony::remove_random_cell(
        std::mt19937 &rng_r)
{
    assert(cells.size() > 0);

    // uniform distribution
    // to sample random cell
    std::uniform_int_distribution<unsigned> 
        random_cell_distribution{0, 
            static_cast<unsigned>(cells.size() - 1)};

    // sample random cell to remove
    unsigned cell_to_remove_idx = random_cell_distribution(rng_r);

    // remove cell from stack by replacing it with last cell
    cells[cell_to_remove_idx] = cells.back();

    // then remove last cell
    cells.pop_back();

    // remove division rate from stack, same fashion
    division_rates[cell_to_remove_idx] = division_rates.back();

    assert(division_rates[cell_to_remove_idx] == 1.0 / cells[cell_to_remove_idx].division);
    division_rates.pop_back();

    assert(division_rates.size() == cells.size());
} // end remove_random_cell()


// select a cell based on the division rate
// in this colony and have it divide into 
// parent and offspring cell
void Colony::select_and_divide(
        std::mt19937 &rng_r,
        Parameters const &param
        )
{
    // set up distribution of division rates
    // from which we sample cells
    std::discrete_distribution <unsigned> 
        division_rate_distribution(
                division_rates.begin(),
                division_rates.end()
                );

    // select cell based on the division rate, but do so 
    // stochastically - hence it is not always the cell with the smallest
    // division time (i.e., largest division rate) that wins
    unsigned parent_cell_idx = division_rate_distribution(rng_r);

    assert(parent_cell_idx < cells.size());

    // go make offspring
    Cell offspring_cell(cells[parent_cell_idx],
            rng_r,
            param);

    // update division rate of parent cell
    // in division rate distribution
    double division = cells[parent_cell_idx].division;

    double division_offspring = offspring_cell.division;

    assert(division > 0.0);
    assert(division_offspring > 0.0);

    // update division rate corrresponding to this cell's index
    division_rates[parent_cell_idx] = 1.0 / division;

    // add offspring to stack
    cells.push_back(offspring_cell);
    
    // add offspring division time to stack
    division_rates.push_back(1.0 / division_offspring);

    // do some bounds checking
    assert(division_rates.size() == cells.size());
} // end select_and_divide()


