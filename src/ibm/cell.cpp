#include <random>
#include "cell.hpp"
#include "parameters.hpp"

// build a cell from parameters
// typically used to build the initial cell of a simulation
// this is similar to create_cell() in the original R script
Cell::Cell(Parameters const &params) :
    b1{params.init_b1}, // damage component 1
    b2{params.init_b2}, // damage component 2
    alpha_m{params.init_alpha_m},
    alpha_int{params.init_alpha_int},
    alpha_grad{params.init_alpha_grad},
    birth{params.init_birth},
    v_int{params.init_v_int},
    v_grad{params.init_v_grad}
{
    alpha = alpha_int + alpha_grad * b1;
    v = v_int + v_grad * b1; // TODO not sure why this is b1 and not b2

    // how generalizable is this function for division time?
    divT = division_time(b1, b2, alpha_m);

    // one only seems to set this variable once // TODO
    division = birth + divT;
}

double Cell::division_time(
        double const b1s,
        double const b2s,
        double const alpha_m_s
        ) const
{
    return(1.0 / (3.0 * b1s * b1s 
            - 1.0 / 3.0 * std::pow(b1s, 3.0) 
            - 2 * b2s * b2s + 4 * b1s * b2s 
            + 100 
            - 1.0/ 20 * std::pow(alpha_m_s, 3.0)));
}

// build an offspring cell from parent
// this is the divide() function in the original 
// R script
Cell::Cell(
        Cell &parent, // non-const reference to parental cell, as we will modify parent too
        std::mt19937 &rng_r, // reference to random number generator
        Parameters const &params// reference to parameter object (for mutation rates etc)
        ) : 
    alpha_int{parent.alpha_int}, // inherit trait loci
    alpha_grad{parent.alpha_grad},
    v_int{parent.v_int},
    v_grad{parent.v_grad},
    birth{parent.birth}// TODO check what this is
{
    // calculate damage values if cells would 
    // be dividing symmetrically
    double b1s{0.5 * (parent.b1 + params.u1)};
    double b2s{0.5 * (parent.b2 + params.u2)};
    
    // build asymmetry transmission phenotypes
    // note parental control over asymmetry
    alpha = parent.alpha_int + parent.alpha_grad * b1s;

    v = v_int + v_grad * b1s;

    // calculate direction vector v using reaction norm with b1s
    double v1_norm = v / (v + 1.0);
    double v2_norm = 1.0 / (v + 1.0);

    // calculate asymmetry in each component
    double a1 = alpha * v1_norm;
    double a2 = alpha * v2_norm;

    a1 = std::min(std::max(a1, 0.0), b1s);
    a2 = std::min(std::max(a2, 0.0), b2s);

    // assign damage to parent
    parent.b1 = b1s + a1;
    parent.b2 = b2s + a2;

    // assign damage to offspring
    b1 = b1s - a1;
    b2 = b2s - a2;

    // assign value of alpha_m to both parent and offspring
    parent.alpha_m = alpha_m =  a1 + a2;

    // calculate new division time for parent
    parent.divT = division_time(parent.b1,
            parent.b2,
            parent.alpha_m
            );

    // calculate division time for offspring
    divT = division_time(
            b1,
            b2,
            alpha_m);

    parent.birth = parent.birth + parent.divT;
    birth = parent.birth + divT;
    division = birth + divT;

    // set up distributions to mutate loci
    std::normal_distribution<double> standard_normal{};
    std::uniform_real_distribution<double> uniform{};

    // mutate the various traits
    if (uniform(rng_r) < params.mu_alpha_int)
    {
        alpha_int += standard_normal(rng_r) * params.sdmu;
    }
    
    if (uniform(rng_r) < params.mu_alpha_grad)
    {
        alpha_grad += standard_normal(rng_r) * params.sdmu;
    }
    
    if (uniform(rng_r) < params.mu_v_int)
    {
        v_int += standard_normal(rng_r) * params.sdmu;
    }
    
    if (uniform(rng_r) < params.mu_v_grad)
    {
        v_grad += standard_normal(rng_r) * params.sdmu;
    }

} // end offspring-from-parent-constructor

// copy constructor
// this is only relevant when you need to 
// move cells around from one vector to
// another without them giving birth to others
Cell::Cell(Cell const &other) :
    b1{other.b1},
    b2{other.b2},
    alpha_m{other.alpha_m},
    alpha_int{other.alpha_int},
    alpha_grad{other.alpha_grad},
    alpha{other.alpha},
    
    v_int{other.v_int},
    v_grad{other.v_grad},
    v{other.v},
    
    birth{other.birth},
    division{other.division},
    divT{other.divT}
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


