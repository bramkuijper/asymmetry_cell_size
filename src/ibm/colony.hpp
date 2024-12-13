#ifndef _COLONY_HPP
#define _COLONY_HPP

#include <vector>
#include "parameters.hpp"
#include "cell.hpp"

class Colony
{
    public:
        std::vector<Cell> cells{}; // the vector of cells of this colony
       
        // store division times in a separate list 
        std::vector<double> division_times;

        Colony(Parameters const &params);

};

#endif 
