#ifndef DIMACSGENERATOR_H
#define DIMACSGENERATOR_H 1

#include <vector>
#include <fstream>
#include "cnfclause.h"
#include "cnfformula.h"
#include "satgenerator.h"

/** A very very basic DIMACS parser. Only parses for cnf formulas. */
class DimacsGenerator : public SatGenerator{
  private:
    std::string filename;
  public:
    /** constructor - reads the formula from the file and creates it
     @param file the file to read
     @param k arity of a clause */
    DimacsGenerator(std::string filename, unsigned int k);
    /** @return sat formula from the file */
    void generate_sat(CNFFormula & f);
};
#endif
