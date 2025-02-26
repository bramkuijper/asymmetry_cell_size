# recipe to build the executable
# compilation on a unix system can be done simply by 
# typing 'make' once in the directory with the source code

CXX=g++
CXXFLAGS=-Wall -O3 -std=c++20

EXE=asymmetry.exe
CPP=main.cpp asymmetry.cpp colony.cpp cell.cpp
HPP=asymmetry.hpp colony.cpp cell.hpp parameters.hpp

$(EXE) : $(CPP) $(HPP)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(CPP)

clean :
	rm -rf $(EXE)
