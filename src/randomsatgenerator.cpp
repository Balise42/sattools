#include <vector>
#include <algorithm>
#include <random>
#include "satgenerator.h"
#include "randomsatgenerator.h"
#include "cnfformula.h"
#include "cnfclause.h"

RandomSatGenerator::RandomSatGenerator(int n, int k, int probrange = 5):SatGenerator(n, k),probrange(probrange){
}

RandomSatGenerator::~RandomSatGenerator(){
}

CNFFormula RandomSatGenerator::generate_formula(){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1,probrange);
  std::vector<std::vector<short> > permutations = generate_permutations();
  for(const auto & permutation : permutations){
    std::vector<CNFClause> allclauses = generate_clauses(permutation);
    for(const auto & clause : allclauses){
      if(dis(gen) == 1){
        formula->add_clause(clause);
      }
    }
  }
  return *formula;
}

CNFFormula RandomSatGenerator::generate_sat(){
  while(1){
    generate_formula();
    formula->bruteforce_solve_sat();
    if(formula->has_satisfying_assignments()){
      return *formula;
    }
  }
}