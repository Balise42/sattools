#ifndef MAXSATGENERATOR_H
#define MAXSATGENERATOR_H 1

#include <vector>
#include "satgenerator.h"
#include "structs.h"
#include "cnfformula.h"
#include "cnfclause.h"

/** Generates a maximum formula from a set of satisfying assignments */
class MaxSatGenerator:public SatGenerator{
  private:
    /** satisfying assignments */
    const std::vector<assignment> assignments;
    bool check_clause(const CNFClause & clause);
  public:
    MaxSatGenerator(unsigned int n, unsigned int k, const std::vector<assignment> & assignments);
    ~MaxSatGenerator();
    CNFFormula generate_sat();
};

#endif
