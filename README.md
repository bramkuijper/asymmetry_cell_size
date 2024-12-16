# Evolving asymmetry in cell size

## Files
The project is written in C++. It is located in the folder `src/ibm` and includes the following files:
* `main.cpp`: starting point of the simulation, as it contains the `main()` function. File that accepts command-line arguments to dynamically change parameters of the simulation.
* `cell.hpp`: header file of the `Cell` class, declaring data members and methods to create / divide a cell
* `cell.cpp`: actual implementation of the various functions belonging to the `Cell` class.
* `colony.hpp`: header file that declares data members and functions of `Colony` class, which contains a single dividing population of `Cell`s.
* `colony.cpp`: implementation of  `Colony` class, which considers a population of `Cell`s. This also contains selection functions in which cells either get randomly purged or selected to divide based on the highest division rate (1/(division time))
* `asymmetry.hpp`: header file of the `Asymmetry` class, which contains the actual simulation of a population of cells
* `asymmetry.cpp`: implementation of the various functions of the `Asymmetry` class. This the heart of the simulation code

## How to run this all?
On any Linux system, do:
```
git clone https://github.com/bramkuijper/asymmetry_cell_size.git
cd asymmetry_cell_size/src/ibm
make
./asymmetry.exe
```

## Simulation output
Output will be stored in the semicolon-separated text file `sim_asymmetry`. Note that at the bottom of the output file there is a listing with parameters, so simply running `read.table()` in R will mix character data with numbers if one is not careful.

There is an `R`-script `plot_output.r` which can be used to make a pdf plot giving you an initial overview. Again on any Linux system with `R`, and the packages `tidyverse` and `patchwork` installed, you can simply run on any bash shell:
```
./plot_output.r sim_asymmetry
```
