#include <vector>
#include "cnfformula.h"
#include "cnfclause.h"
#include "satgenerator.h"

class RandomSatGenerator {
  private:
    const int k;
    const int n;
    CNFFormula formula;
    /** TODO clean up and proper inheritance */
    SatGenerator * satgenerator;
  public:
    RandomSatGenerator(int n, int k);
    CNFFormula generate_formula();
    CNFFormula get_satisfiable_formula();
};
