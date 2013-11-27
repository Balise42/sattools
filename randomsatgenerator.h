#include <vector>
#include "cnfformula.h"
#include "cnfclause.h"
#include "satgenerator.h"

class RandomSatGenerator:public SatGenerator {
  public:
    RandomSatGenerator(int n, int k);
    ~RandomSatGenerator();
    CNFFormula generate_formula();
    CNFFormula generate_sat();
};
