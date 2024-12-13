# Evolving asymmetry in cell size: damage in 2 components

## Files
The project includes the following files:
* `main.cpp`: starting point of the simulation, as it contains the `main()` function. File that accepts command-line arguments to dynamically change parameters of the simulation.
* `cell.hpp`: header file of the `Cell` class, declaring data members and methods to create / divide a cell
* `cell.cpp`: actual implementation of the various functions belonging to the `Cell` class.
* `colony.hpp`: header file that declares data members and functions of `Colony` class, which contains a single dividing population of `Cell`s.
* `colony.cpp`: implementation of  `Colony` class, which considers a population of `Cell`s.
* `asymmetry.hpp`: header file of the `Asymmetry` class, which contains the actual simulation of a population of cells
* `asymmetry.cpp`: implementation of the various functions of the `Asymmetry` class. This the heart of the simulation code
