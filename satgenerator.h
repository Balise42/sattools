#ifndef SATGENERATOR_H
#define SATGENERATOR_H 1

#include <vector>
#include "cnfclause.h"
#include "cnfformula.h"

class SatGenerator{
  protected:
    /** number of variables */
    const unsigned int n;
    /** max number of literals in a clause ("k-SAT") */
    const unsigned int k;
    /** resulting formula */
    CNFFormula * formula;
    std::vector<std::vector<short> > generate_permutations();
    std::vector<CNFClause> generate_clauses(const std::vector<short> & permutation, int start=0);
    bool check_clause(const CNFClause & clause);
  public:
    SatGenerator(unsigned int n, unsigned int k);
    ~SatGenerator();
    virtual CNFFormula generate_sat()=0;
};

#endif
