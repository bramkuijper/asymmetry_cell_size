#include "asymmetry.hpp"
#include "parameters.hpp"

// the part of the code that takes parameters 
// from the command line and actually runs the thing

int main(int argc, char **argv)
{
    Parameters pars;
    Asymmetry sim(pars);

    sim.run();
}
