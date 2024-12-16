#include <cassert>
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
    data_file << std::endl 
        << std::endl 
        << "seed;" << seed << std::endl
        << "ncolories;" << param.ncolonies << std::endl
        << "min_cells_colony;" << param.min_cells_colony << std::endl
        << "max_cells_colony;" << param.max_cells_colony << std::endl
        << "u1;" << param.u1 << std::endl
        << "u2;" << param.u2 << std::endl
        << "mu_alpha_int;" << param.mu_alpha_int << std::endl
        << "mu_alpha_grad;" << param.mu_alpha_grad << std::endl
        << "mu_v_int;" << param.mu_v_int << std::endl
        << "mu_v_grad;" << param.mu_v_grad << std::endl
        << "sdmu;" << param.sdmu << std::endl
        << "init_alpha_m;" << param.init_alpha_m << std::endl
        << "init_b1;" << param.init_b1 << std::endl
        << "init_b2;" << param.init_b2 << std::endl
        << "init_alpha_int;" << param.init_alpha_int << std::endl
        << "init_alpha_grad;" << param.init_alpha_grad << std::endl
        << "init_v_int;" << param.init_v_int << std::endl
        << "init_v_grad;" << param.init_v_grad << std::endl
        << "init_birth;" << param.init_birth << std::endl;
}

// write the headers of the data file
void Asymmetry::write_data_headers()
{
    data_file << "time" << ";"
                    << "n" << ";"
                    << "mean_b1" << ";"
                    << "mean_b2" << ";"
                    << "mean_alpha_m" << ";"
                    << "mean_alpha_int" << ";"
                    << "mean_alpha_grad" << ";"
                    << "mean_alpha" << ";"
                    << "mean_v_int" << ";"
                    << "mean_v_grad" << ";"
                    << "mean_v" << ";"
                    << "mean_birth" << ";"
                    << "mean_division" << ";"
                    << "mean_divT" << ";"
                    << "var_b1" << ";"
                    << "var_b2" << ";"
                    << "var_alpha_m" << ";"
                    << "var_alpha_int" << ";"
                    << "var_alpha_grad" << ";"
                    << "var_alpha" << ";"
                    << "var_v_int" << ";"
                    << "var_v_grad" << ";"
                    << "var_v" << ";"
                    << "var_birth" << ";"
                    << "var_division" << ";"
                    << "var_divT" << ";" << std::endl;
}

void Asymmetry::write_data()
{
    double mean_b1{0.0};
    double mean_b2{0.0};
    double mean_alpha_m{0.0};
    double mean_alpha_int{0.0};
    double mean_alpha_grad{0.0};
    double mean_alpha{0.0};
    double mean_v_int{0.0};
    double mean_v_grad{0.0};
    double mean_v{0.0};
    double mean_birth{0.0};
    double mean_division{0.0};
    double mean_divT{0.0};

    // now sums of squares for variances
    double ss_b1{0.0};
    double ss_b2{0.0};
    double ss_alpha_m{0.0};
    double ss_alpha_int{0.0};
    double ss_alpha_grad{0.0};
    double ss_alpha{0.0};
    double ss_v_int{0.0};
    double ss_v_grad{0.0};
    double ss_v{0.0};
    double ss_birth{0.0};
    double ss_division{0.0};
    double ss_divT{0.0};

    // aux placeholder for the trait
    double x;

    unsigned n{0};

    // go through all colonies and select cell that will divide
    for (auto metapopulation_iter = metapopulation.begin();
            metapopulation_iter != metapopulation.end();
            ++metapopulation_iter)
    {
        for (auto cell_iter = metapopulation_iter->cells.begin();
                cell_iter != metapopulation_iter->cells.end();
                ++cell_iter)
        {
            x = cell_iter->b1;
            mean_b1 += x;
            ss_b1 += x*x;

            x = cell_iter->b2;
            mean_b2 += x;
            ss_b2 += x*x;

            x = cell_iter->alpha_m;
            mean_alpha_m += x;
            ss_alpha_m += x * x;
            
            x = cell_iter->alpha_int;
            mean_alpha_int += x;
            ss_alpha_int += x * x;

            x = cell_iter->alpha_grad;
            mean_alpha_grad += x;
            ss_alpha_grad += x * x;
            
            x = cell_iter->alpha;
            mean_alpha += x;
            ss_alpha += x * x;

            x = cell_iter->v_int;
            mean_v_int += x;
            ss_v_int += x * x;

            x = cell_iter->v_grad;
            mean_v_grad += x;
            ss_v_grad += x * x;
            
            x = cell_iter->v;
            mean_v += x;
            ss_v += x * x;

            x = cell_iter->birth;
            mean_birth += x;
            ss_birth += x * x;

            x = cell_iter->division;
            mean_division += x;
            ss_division += x * x;

            x = cell_iter->divT;
            mean_divT += x;
            ss_divT += x * x;
        } // end cell_iter

        n += metapopulation_iter->cells.size();
    }

    mean_b1 /= n;
    mean_b2 /= n;
    mean_alpha_m /= n;
    mean_alpha_int /= n;
    mean_alpha_grad /= n;
    mean_alpha /= n;
    mean_v_int /= n;
    mean_v_grad /= n;
    mean_v /= n;
    mean_birth /= n;
    mean_division /= n;
    mean_divT /= n;
    
    double var_b1 = ss_b1/n - mean_b1 * mean_b1; 
    double var_b2 = ss_b2/n - mean_b2 * mean_b2; 
    double var_alpha_m = ss_alpha_m/n - mean_alpha_m * mean_alpha_m; 
    double var_alpha_int = ss_alpha_int/n - mean_alpha_int * mean_alpha_int; 
    double var_alpha_grad = ss_alpha_grad/n - mean_alpha_grad * mean_alpha_grad; 
    double var_alpha = ss_alpha/n - mean_alpha * mean_alpha; 
    double var_v_int = ss_v_int/n - mean_v_int * mean_v_int; 
    double var_v_grad = ss_v_grad/n - mean_v_grad * mean_v_grad; 
    double var_v = ss_v/n - mean_v * mean_v; 
    double var_birth = ss_birth/n - mean_birth * mean_birth; 
    double var_division = ss_division/n - mean_division * mean_division; 
    double var_divT = ss_divT/n - mean_divT * mean_divT; 


    data_file << time_step << ";"
                    << n << ";"
                    << mean_b1 << ";"
                    << mean_b2 << ";"
                    << mean_alpha_m << ";"
                    << mean_alpha_int << ";"
                    << mean_alpha_grad << ";"
                    << mean_alpha << ";"
                    << mean_v_int << ";"
                    << mean_v_grad << ";"
                    << mean_v << ";"
                    << mean_birth << ";"
                    << mean_division << ";"
                    << mean_divT << ";"
                    << var_b1 << ";"
                    << var_b2 << ";"
                    << var_alpha_m << ";"
                    << var_alpha_int << ";"
                    << var_alpha_grad << ";"
                    << var_alpha << ";"
                    << var_v_int << ";"
                    << var_v_grad << ";"
                    << var_v << ";"
                    << var_birth << ";"
                    << var_division << ";"
                    << var_divT << ";" << std::endl;
}

// the function that runs the actual simulation
void Asymmetry::run()
{

    for (time_step = 0; time_step < params.max_time_step; ++time_step)
    {
        // go through all colonies and select cell that will divide
        for (auto metapopulation_iter = metapopulation.begin();
                metapopulation_iter != metapopulation.end();
                ++metapopulation_iter)
        {
            if (metapopulation_iter->cells.size() == 
                    param.max_cells_colony)
            {
                metapopulation_iter->remove_random_cell(rng_r);
            }

            metapopulation_iter->select_and_divide(rng_r, param);

        } // end for metapopulation_iter
        
        if (time_step % params.output_interval == 0)
        {
            write_data();
        }
    }

    write_parameters();
} // end run


