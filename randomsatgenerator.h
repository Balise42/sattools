#include <vector>
#include "cnfformula.h"
#include "cnfclause.h"
#include "satgenerator.h"

class RandomSatGenerator:public SatGenerator {
  private:
    int probrange;
  public:
    RandomSatGenerator(int n, int k, int probrange);
    ~RandomSatGenerator();
    CNFFormula generate_formula();
    CNFFormula generate_sat();
};
