#include <vector>
#include "cnfformula.h"
#include "cnfclause.h"
#include "satgenerator.h"

class RandomSatGenerator:public SatGenerator {
  private:
    /** probability range - we will pick 1 out of probrange clauses on average*/
    int probrange;
  public:
    /** default constructor 
     @param n number of variables
     @param k arity of clause
     @param probrange range of probability: we will pick 1 out of probrange clauses */
    RandomSatGenerator(int n, int k, int probrange);
    /** destructor */
    ~RandomSatGenerator();
    /** generates a random formula given the parameters */
    CNFFormula generate_formula();
    /** loops the formula generation until it finds a satisfiable formula */
    CNFFormula generate_sat();
};
