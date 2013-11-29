#ifndef DIMACSGENERATOR_H
#define DIMACSGENERATOR_H 1

#include <vector>
#include <fstream>
#include "cnfclause.h"
#include "cnfformula.h"
#include "satgenerator.h"

/** A very very bad DIMACS parser. TODD: sanitize input. */
class DimacsGenerator : public SatGenerator{
  public:
    DimacsGenerator(std::ifstream & file, int k);
    CNFFormula generate_sat();
};
#endif
