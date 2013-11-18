#include <vector>
#include <algorithm>
#include <random>
#include "satgenerator.h"
#include "randomsatgenerator.h"
#include "cnfformula.h"
#include "cnfclause.h"

RandomSatGenerator::RandomSatGenerator(int n, int k):n(n),k(k),formula(CNFFormula(n,k)), satgenerator(new SatGenerator(n, k, 0, std::vector<assignment>(0))){
}

CNFFormula RandomSatGenerator::generate_formula(){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0,8);
  std::vector<std::vector<short> > permutations = satgenerator->generate_permutations();
  for(const auto & permutation : permutations){
    std::vector<CNFClause> allclauses = satgenerator->generate_clauses(permutation);
    for(const auto & clause : allclauses){
      if(dis(gen) == 0){
        formula.add_clause(clause);
      }
    }
  }
  return formula;
}

CNFFormula RandomSatGenerator::get_satisfiable_formula(){
  while(1){
    generate_formula();
    formula.bruteforce_solve_sat();
    if(formula.has_satisfying_assignments()){
      return formula;
    }
  }
}
