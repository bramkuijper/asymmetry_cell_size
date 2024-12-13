#include "asymmetry.hpp"

// the class constructor that builds the simulation object
Asymmetry::Asymmetry(Parameters const &parameter_object) :
    rd{} // initialize random device that itself finds a random seed
    ,params{parameter_object} // initialize data member containing all the parameters
    ,seed{rd()} // initialize the seed
    ,rng_r{seed} // start the random number generator
    ,uniform{0.0,1.0} // initialize uniform distribution to translate probabilities into events
    ,colony_sampler{0, param.ncolonies - 1 } // uniform distribution to randomly sample colonies
    ,metapopulation(param.ncolonies, Colony(param)) // initialize all the colonies
    ,data_file{param.file_name} // initialize the output file
{
    // provide headers to the output file
    write_data_headers();
}

// write the parameters to the output file
void Asymmetry::write_parameters()
{
    data_file << std::endl <<
        << std::endl <<
        << "seed" << seed << std::endl
        << "ncolories" << par.ncolonies << std::endl
        << "min_cells_colony" << par.min_cells_colony << std::endl
        << "max_cells_colony" << par.max_cells_colony << std::endl
        << "u1" << par.u1 << std::endl
        << "u2" << par.u2 << std::endl
        << "mu_alpha_int" << par.mu_alpha_int << std::endl
        << "mu_alpha_grad" << par.mu_alpha_grad << std::endl
        << "mu_v_int" << par.mu_v_int << std::endl
        << "mu_v_grad" << par.mu_v_grad << std::endl
        << "sdmu" << par.sdmu << std::endl
        << "init_alpha_m" << par.init_alpha_m << std::endl
        << "init_b1" << par.init_b1 << std::endl
        << "init_b2" << par.init_b2 << std::endl
        << "init_alpha_int" << par.init_alpha_int << std::endl
        << "init_alpha_grad" << par.init_alpha_grad << std::endl
        << "init_v_int" << par.init_v_int << std::endl
        << "init_v_grad" << par.init_v_grad << std::endl
        << "init_birth;" << par.init_birth << std::endl;
}

// write the headers of the data file
void Asymmetry::write_data_headers()
{
    data_file << "time;" << std::endl;
}

// the function that runs the actual simulation
void Asymmetry::run()
{
    unsigned parent_cell_idx;

    for (time_step = 0; time_step < params.max_time_step; ++time_step)
    {
        // go through all colonies and select cell that will divide
        for (auto metapopulation_iter = metapopulation.begin();
                metapopulation_iter != metapopulation.end();
                ++metapopulation_iter)
        {
            std::discrete_distribution <unsigned> 
                division_time_distribution(
                        metapopulation_iter->division_times.begin(),
                        metapopulation_iter->division_times.end()
                        );

            // select cell based on the division rate, but do so 
            // stochastically - hence it is not always the cell with the smallest
            // division time (i.e., largest division rate) that wins
            parent_cell_idx = division_time_distribution(rng_r);

        }
    }
    
} // end run

// function that writes parameters etc and does other postprocessing work
void Asymmetry::finalize()
{


} // end finalize
