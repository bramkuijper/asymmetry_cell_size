#ifndef _CELL_HPP_
#define _CELL_HPP_

#include <random>
#include "parameters.hpp"

class Cell
{
    public:

        double b1{0.0}; // damage component 1
        double b2{0.0}; // damage component 2
        double alpha_m{0.0}; // ?
        double alpha_int{0.0}; // intercept of the alpha reaction norm
        double alpha_grad{0.0}; // gradient of the alpha reaction norm
        double alpha{0.0}; // resulting value of alpha

        double v_int{0.0}; // intercept of the v reaction norm
        double v_grad{0.0}; // gradient of the v reaction norm
        double v{0.0}; // resulting value of v
        
        double birth{0.0}; // a cell's birth rate
        double division{0.0}; // a cell's total division time
        double divT{0.0}; // a cell's division time

        // generate a cell from parameters (typically used when 
        // initializing a colony)
        Cell(Parameters const &params);

        // generate a cell from its parents 
        // this is the divide() function in the original
        // R script
        Cell(Cell &other,
                std::mt19937 &rng_r,
                Parameters const &params);

        // copy constructor
        // this is only relevant when you need to 
        // move cells around from one vector to
        // another without them giving birth to others
        Cell(Cell const &other);

        // overload the assignment operator so that 
        // all data is transmitted when 'assigning' one
        // cell to another
        void operator=(Cell const &other);

        // function that calculates division time
        double division_time();
}; // end declaration of Cell() class

#endif
