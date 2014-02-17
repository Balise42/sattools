#ifndef SATGENERATOR_H
#define SATGENERATOR_H 1

#include <vector>
#include "cnfclause.h"
#include "cnfformula.h"

/** generic sat generator - to be inherited by variaous generators */
class SatGenerator{
  protected:
    /** number of variables */
    unsigned int n;
    /** max number of literals in a clause ("k-SAT") / arity of a clause */
    const unsigned int k;
    /** generate all sets of k variables among n variables
      @return a vector of size "n choose k" of vector of size n with k bits set to 1 */
    std::vector<std::vector<short> > generate_permutations();
    /** generate all clauses corresponding to a given set of variables
    @param permutation the set of variables to use (vector of size n where k bits are set to 1
    @param start used for the recursive works only, user should not set it (default to 0)
    @return all the clauses corresponding to the permutation - 2^k possibilities */
    std::vector<CNFClause> generate_clauses(const std::vector<short> & permutation, int start=0);
  public:
    /** default constructor*/
    SatGenerator(unsigned int n, unsigned int k);
    /** destructor */
    ~SatGenerator();
    /** virtual - needs to be implemented by generator - returns a generated formula */
    virtual void generate_sat(CNFFormula & f)=0;
};

#endif
