#include <vector>
#include <algorithm>
#include "maxsatgenerator.h"

/** default constructor, creates the object and makes default assignments 
    @param n number of variables
    @param k number of literals in the generated clauses 
    @param nsat number of satisfying assignments
    @param assignments the satisfying assignments for which we want a formula */
MaxSatGenerator::MaxSatGenerator(unsigned int n, unsigned int k, unsigned int nsat, const std::vector<assignment> & assignments):n(n), k(k), nsat(nsat), assignments(assignments), formula(new CNFFormula(n, k)){
}

MaxSatGenerator::~MaxSatGenerator(){
  delete formula;
}

/** generate all sets of k variables among n variables
    @return a vector of size "n choose k" of vector of size n with k bits set to 1 */
std::vector<std::vector<short> > MaxSatGenerator::generate_permutations(){
  std::vector<short> initperm(n, 0);
  std::vector<std::vector<short> > permutations;
  for(unsigned int i = 0; i<k; i++){
    initperm[i] = 1;
  }
  do {
    permutations.push_back(initperm);
  } while(std::prev_permutation(initperm.begin(), initperm.end()));

  return permutations;
}

/** generate all clauses corresponding to a given set of variables
    @param permutation the set of variables to use (vector of size n where k bits are set to 1
    @param start used for the recursive works only, user should not set it (default to 0)
    @return all the clauses corresponding to the permutation - 2^k possibilities */
std::vector<CNFClause> MaxSatGenerator::generate_clauses(const std::vector<short> & permutation, int start){
  std::vector<CNFClause> clauses;
  for(unsigned int i = start; i<n; i++){
    if(permutation[i] == 1){
      literal l0;
      l0.variable = i;
      l0.value = 0;
      literal l1;
      l1.variable = i;
      l1.value = 1; 

      std::vector<CNFClause> tempclauses = generate_clauses(permutation, i+1);
      //if no partial clause then we create the two initializing clauses
      if(tempclauses.size() == 0){
        clauses.push_back(CNFClause(std::vector<literal>(1, l0)));
        clauses.push_back(CNFClause(std::vector<literal>(1, l1)));
        return clauses;
      }
      else{
        std::vector<CNFClause> tempclauses2 = tempclauses;
        for_each(tempclauses.begin(), tempclauses.end(), std::bind2nd(std::mem_fun_ref(&CNFClause::add_literal), l1));
        clauses.insert(clauses.begin(), tempclauses.begin(), tempclauses.end());
        for_each(tempclauses2.begin(), tempclauses2.end(), std::bind2nd(std::mem_fun_ref(&CNFClause::add_literal), l0));
        clauses.insert(clauses.begin(), tempclauses2.begin(), tempclauses2.end());
        return clauses;
      }
    }
  }
  //stop condition of the recursion
  return std::vector<CNFClause>(0);
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

