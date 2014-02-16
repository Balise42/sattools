#include <vector>
#include <algorithm>
#include "maxsatgenerator.h"

MaxSatGenerator::MaxSatGenerator(unsigned int n, unsigned int k, const std::vector<assignment> & assignments):SatGenerator(n,k), assignments(assignments){
}

MaxSatGenerator::~MaxSatGenerator(){
}

CNFFormula MaxSatGenerator::generate_sat(){
  std::vector<std::vector<short> > permutations = generate_permutations();
  for(const auto & permutation : permutations){
    std::vector<CNFClause> allclauses = generate_clauses(permutation);
    for(const auto & clause : allclauses){
      if(check_clause(clause)){
        formula->add_clause(clause);
      }
    }
  }
  return *formula;
}

bool MaxSatGenerator::check_clause(const CNFClause & clause){
  for(const auto & assignment : assignments){
    if(!clause.check_bitstring(assignment)){
      return false;
    }
  }
  return true;
}

