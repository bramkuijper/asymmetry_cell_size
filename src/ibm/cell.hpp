#ifndef _CELL_HPP_
#define _CELL_HPP_

#include <random>
#include "parameters.hpp"

class Cell
{
    public:

        double b1{0.0}; // ?
        double b2{0.0}; // ?
        double alpha_m{0.0}; // ?
        double alpha_int{0.0}; // intercept of the alpha reaction norm
        double alpha_grad{0.0}; // gradient of the alpha reaction norm
        double alpha{0.0}; // resulting value of alpha

        double v_int{0.0}; // intercept of the v reaction norm
        double v_grad{0.0}; // gradient of the v reaction norm
        double v{0.0}; // resulting value of v
        
        double birth{0.0};
        double division{0.0};
        double divT{0.0};

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
