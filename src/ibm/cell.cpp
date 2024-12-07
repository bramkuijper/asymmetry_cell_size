
#include <random>
#include "cell.hpp"
#include "parameters.hpp"

// build a cell with parameters (typically the initial cell of a colony)
Cell::Cell(Parameters const &params)
{}

// build a daughter cell 
Cell::Cell(Cell const &other,
        std::mt19937 &rng_r,
        Parameters const &params) 
{}
