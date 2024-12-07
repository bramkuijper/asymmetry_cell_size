#ifndef _CELL_HPP_
#define _CELL_HPP_

#include <random>
#include "parameters.hpp"

class Cell
{
    public:

        // generate a cell from parameters (typically used when 
        // initializing a colony)
        Cell(Parameters const &params);

        // generate a cell from its parents (used when 
        // performing cell division
        Cell(Cell const &other,
                std::mt19937 &rng_r,
                Parameters const &params);

};

#endif
