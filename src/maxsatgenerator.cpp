#include <vector>
#include <algorithm>
#include "maxsatgenerator.h"

MaxSatGenerator::MaxSatGenerator(unsigned int n, unsigned int k, const std::vector<assignment> & assignments):SatGenerator(n,k), assignments(assignments){
}

MaxSatGenerator::~MaxSatGenerator(){
}

void MaxSatGenerator::generate_sat(CNFFormula & f){
  f = CNFFormula(n,k);
  std::vector<std::vector<short> > permutations = generate_permutations();
  for(const auto & permutation : permutations){
    std::vector<CNFClause> allclauses = generate_clauses(permutation);
    for(const auto & clause : allclauses){
      if(check_clause(clause)){
        f.add_clause(clause);
      }
    }
  }
}

bool MaxSatGenerator::check_clause(const CNFClause & clause){
  for(const auto & assignment : assignments){
    if(!clause.check_bitstring(assignment)){
      return false;
    }
  }
  return true;
}

