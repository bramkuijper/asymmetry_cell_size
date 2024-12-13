#ifndef _ASYMMETRY_HPP_
#define _ASYMMETRY_HPP_

#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include "colony.hpp"
#include "parameters.hpp"

class Asymmetry
{
    private:
        unsigned time_step{0};
        
        // random device which is used to generate
        // proper random seeds
        std::random_device rd;

        // parameters for this simulation
        Parameters param{};
        
        // store the random seed
        // we need to store this so that we can output the
        // random seed, so that we could 'replay' the exact
        // same sequence of random numbers for debugging purposes etc
        unsigned int seed;

        // random number generator
        std::mt19937 rng_r;

        // uniform distribution to compare against probabilities
        std::uniform_real_distribution<double> uniform;

        // uniform distribution to get random patch
        std::uniform_int_distribution<unsigned> colony_sampler;

        Parameters params{};
        
        // a metapopulation of patches containing individuals
        std::vector <Colony> metapopulation;

        // data file for output 
        std::ofstream data_file;


        // functions etc
        void write_data_headers(); // writes headers to the output file
        void finalize(); // postprocessing work


    public:
        Asymmetry(Parameters const &parameter_object);
        void run(); // runs the actual simulation



};

#endif
