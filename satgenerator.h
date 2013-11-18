#ifndef SATGENERATOR_H
#define SATGENERATOR_H 1

#include <vector>
#include "structs.h"
#include "cnfformula.h"
#include "cnfclause.h"

/** Generates a formula from a set of satisfying assignments */
class SatGenerator{
  private:
    /** number of variables */
    const unsigned int n;
    /** max number of literals in a clause ("k-SAT") */
    const unsigned int k;
    /** number of satisfying assignments */
    const unsigned int nsat;
    /** satisfying assignments */
    const std::vector<assignment> assignments;
    /** resulting formula */
    CNFFormula * formula;
    std::vector<std::vector<short> > generate_permutations();
    std::vector<CNFClause> generate_clauses(const std::vector<short> & permutation, int start=0);
    bool check_clause(const CNFClause & clause);
  public:
    SatGenerator(unsigned int n, unsigned int k, unsigned int nsat, const std::vector<assignment> & assignments);
    ~SatGenerator();
    CNFFormula generate_sat();
    friend class RandomSatGenerator;
};

#endif
