#ifndef MAXSATGENERATOR_H
#define MAXSATGENERATOR_H 1

#include <vector>
#include "satgenerator.h"
#include "structs.h"
#include "cnfformula.h"
#include "cnfclause.h"
#include "assignment.h"

/** Generates a maximum formula from a set of satisfying assignments */
class MaxSatGenerator:public SatGenerator{
  private:
    /** satisfying assignments */
    const std::vector<Assignment> assignments;
    /** checks whether a clause satisfies all satisfying assignments */
    bool check_clause(const CNFClause & clause);
  public:
    /** default constructor, creates the object and makes default assignments 
    @param n number of variables
    @param k number of literals in the generated clauses 
    @param nsat number of satisfying assignments
    @param assignments the satisfying assignments for which we want a formula */
    MaxSatGenerator(unsigned int n, unsigned int k, const std::vector<Assignment> & assignments);
    /** default destructor */
    ~MaxSatGenerator();
    /** generate all clauses and put the valid one in the returned formula */
    void generate_sat(CNFFormula & f);
};

#endif
