#ifndef _PARAMETERS_HPP
#define _PARAMETERS_HPP

#include <string>

class Parameters
{
    public:
        
        // total number of colonies in the metapopulation
        unsigned ncolonies{200};

        // minimum and starting number of cells in a colony
        unsigned min_cells_colony{1};

        // max number of cells in colony before sporulation
        unsigned max_cells_colony{100};

        // maximum number of time steps the simulation runs
        unsigned long max_time_step{1000};

        // accumulation of damage for the two components
        double u[2]{0.0,0.0};

        // mutation rates of baseline division asymmetry for each
        // of the two damage components (the intercept)
        double mu_alpha[2]{0.01,0.01}; 
        
        // mutation rates of plasticity in division asymmetry for each
        // of the two damage components (the reaction norm slope)
        double mu_alpha_grad[2]{0.01,0.01};

        // name of the output file name
        std::string file_name{"sim_asymmetry"};
};


#endif
