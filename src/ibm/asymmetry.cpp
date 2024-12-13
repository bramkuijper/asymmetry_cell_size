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

// write the headers of the data file
void Asymmetry::write_data_headers()
{
    data_file << "time;" << std::endl;
}

// the function that runs the actual simulation
void Asymmetry::run()
{
    for (time_step = 0; time_step < params.max_time_step; ++time_step)
    {


    }
    
} // end run

// function that writes parameters etc and does other postprocessing work
void Asymmetry::finalize()
{


} // end finalize
