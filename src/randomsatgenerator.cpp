#include <vector>
#include <algorithm>
#include <random>
#include "satgenerator.h"
#include "randomsatgenerator.h"
#include "cnfformula.h"
#include "cnfclause.h"
#include "solvedcnf.h"

RandomSatGenerator::RandomSatGenerator(int n, int k, int probrange = 5):SatGenerator(n, k),probrange(probrange){
}

RandomSatGenerator::~RandomSatGenerator(){
}

void RandomSatGenerator::generate_formula(CNFFormula & f){
  f = CNFFormula(n, k);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1,probrange);
  std::vector<std::vector<short> > permutations = generate_permutations();
  for(const auto & permutation : permutations){
    std::vector<CNFClause> allclauses = generate_clauses(permutation);
    for(const auto & clause : allclauses){
      if(dis(gen) == 1){
        f.add_clause(clause);
      }
    }
  }
}

void RandomSatGenerator::generate_sat(CNFFormula & f){
  while(1){
    generate_formula(f);
    SolvedCNF solf(f);
    if(solf.has_satisfying_assignments()){
      break;
    }
  }
}
