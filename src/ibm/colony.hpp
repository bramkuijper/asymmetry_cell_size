#ifndef _COLONY_HPP
#define _COLONY_HPP

#include <vector>
#include "parameters.hpp"
#include "cell.hpp"

class Colony
{
    public:
        std::vector<Cell> Cells{}; // the vector of cells of this colony

        Colony(Parameters const &params);

};

#endif 
