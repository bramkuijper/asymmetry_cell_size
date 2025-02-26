#ifndef _PARAMETERS_HPP
#define _PARAMETERS_HPP

#include <string>

class Parameters
{
    public:
        
        // total number of colonies in the metapopulation
        unsigned ncolonies{10};

        // minimum and starting number of cells in a colony
        unsigned min_cells_colony{1};

        // max number of cells in colony before sporulation
        unsigned max_cells_colony{100000};

        // maximum number of time steps the simulation runs
        unsigned long max_time_step{10000};

        // accumulation of damage for the two components
        double u1{4.5};
        double u2{4.5};

        // mutation rates of intercept in division asymmetry for 
        // damage component 1
        double mu_alpha_int{0.01}; 
        
        // mutation rates of plasticity in division asymmetry for 
        // damage component 1
        double mu_alpha_grad{0.005};
        
        // mutation rates of intercept in division asymmetry for 
        // damage component 2
        double mu_v_int{0.01}; 
        
        // mutation rates of plasticity in division asymmetry for 
        // damage component 2
        double mu_v_grad{0.05};

        double sdmu{0.05};

        double init_alpha_m{0.0};
        double init_b1{0.0};
        double init_b2{0.0};

        double init_alpha_int{37}; // TODO: what should be the proper starting val here
        double init_alpha_grad{-7.5}; 

        double init_v_int{2.4}; 
        double init_v_grad{-0.3}; 

        double init_birth{0.5}; // TODO what the hell should we take here as initial value

        // name of the output file name
        std::string file_name{"sim_asymmetry"};
        std::string distribution_file_name{"sim_asymmetry_distribution"};

        unsigned output_interval{1};
};


#endif
