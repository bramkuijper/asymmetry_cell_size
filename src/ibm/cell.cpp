
#include <random>
#include "cell.hpp"
#include "parameters.hpp"

// build a cell with parameters (typically the initial cell of the simulation)
Cell::Cell(Parameters const &params) :
    b1{params.init_b1},
    b2{params.init_b2},
    alpha_m{params.init_alpha_m}
    alpha_int{params.alpha_int_init},
    alpha_grad{params.alpha_grad_init},
{}

// build an offspring cell from parent
Cell::Cell(
        Cell const &parent, // reference to parental cell
        std::mt19937 &rng_r, // reference to random number generator
        Parameters const &params) : // reference to parameter object
    alpha_int{parent.alpha_int},
    alpha_grad{parent.alpha_grad},
    v_int{parent.v_int},
    v_grad{parent.v_grad},
    birth{parent.birth}// TODO check this
{
    std::normal_distribution<double> standard_normal{};
    std::uniform_real_distribution<double> uniform{};

    // mutate the various traits
    if (uniform(rng_r) < par.mu_alpha_int)
    {
        alpha_int += standard_normal(rng_r) * par.sdmu;
    }
    
    if (uniform(rng_r) < par.mu_alpha_grad)
    {
        alpha_grad += standard_normal(rng_r) * par.sdmu;
    }
    
    if (uniform(rng_r) < par.mu_v_int)
    {
        v_int += standard_normal(rng_r) * par.sdmu;
    }
    
    if (uniform(rng_r) < par.mu_v_grad)
    {
        v_grad += standard_normal(rng_r) * par.sdmu;
    }

    // build phenotypes
    alpha = alpha_int + alpha_grad * b1;
    v = v_int + v_grad * b1;

    // how generalizable is this function for division time?
    divT = 1.0 / (3.0 * b1 * b1 
            - 1.0 / 3.0 * std::pow(b1, 3.0) 
            - 2 * b2 * b2 + 4 * b1 * b2 
            + 100 
            - 1.0/ 20 * std::pow(alpha_m, 3.0))

    division = birth + divT;
} // end offspring-from-parent-constructor

// copy constructor
Cell::Cell(Cell const &other) :
    b1{other.b1};
    b2{other.b2};
    alpha_m{other.alpha_m};
    alpha_int{other.alpha_int};
    alpha_grad{other.alpha_grad};
    alpha{other.alpha};
    
    v_int{other.v_int};
    v_grad{other.v_grad};
    v{other.v};
    
    birth{other.birth};
    division{other.division};
    divT{other.divT};
{} // end copy constructor

// assignment operator
void Cell::operator=(Cell const &other)
{
    b1 = other.b1;
    b2 = other.b2;
    alpha_m = other.alpha_m;
    alpha_int = other.alpha_int;
    alpha_grad = other.alpha_grad;
    alpha = other.alpha;
    
    v_int = other.v_int;
    v_grad = other.v_grad;
    v = other.v;
    
    birth = other.birth;
    division = other.division;
    divT = other.divT;
}// end assignment operator


