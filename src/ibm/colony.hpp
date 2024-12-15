#ifndef _COLONY_HPP
#define _COLONY_HPP

#include <vector>
#include <random>
#include "parameters.hpp"
#include "cell.hpp"

class Colony
{
    public:
        std::vector<Cell> cells{}; // the vector of cells of this colony
       
        // store division times in a separate list 
        std::vector<double> division_rates;

        // colony constructor that starts the colony with initial cell(s)
        Colony(Parameters const &params);

        // remove a random cell
        void remove_random_cell(std::mt19937 &rng_r);

        void select_and_divide(std::mt19937 &rng_r,
                Parameters const &param);
};

#endif 
