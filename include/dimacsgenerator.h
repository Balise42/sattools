#ifndef DIMACSGENERATOR_H
#define DIMACSGENERATOR_H 1

#include <vector>
#include <fstream>
#include "cnfclause.h"
#include "cnfformula.h"
#include "satgenerator.h"

/** A very very basic DIMACS parser. Only parses for cnf formulas. */
class DimacsGenerator : public SatGenerator{
  public:
    /** constructor - reads the formula from the file and creates it
     @param file the file to read
     @param k arity of a clause */
    DimacsGenerator(std::ifstream & file, int k);
    /** @return sat formula from the file */
    CNFFormula generate_sat();
};
#endif
