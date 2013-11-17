#include <vector>
#include <algorithm>
#include "cnfformula.h"

/** creates a CNF formula with the given clauses and assignments, with default empty clause and empty assignment vectors */
CNFFormula::CNFFormula(int n, int k, const std::vector<CNFClause> & clauses, const std::vector<assignment> assignments):n(n), k(k), clauses(clauses),unchecked_assignments(assignments){
}

/** solves a CNF formula by brute force - going to all 2^n assignments.
    assigns satisfying_assignments to contain the satisfying assignments
    and sets was_solved to true. if was_solved is already set to true then we do
    not re-solve.*/
void CNFFormula::bruteforce_solve_sat(){
  // we don't want to re-solve if it has already been solved
  if(was_solved){
    return;
  }

  std::vector<short> bitstring;
  //we enumerate all the bitstrings by taking all permutations of strings
  //that have i bits to 1
  for(int i = 0; i<=n; i++){
    bitstring = std::vector<short>(n, 0);
    for(int j = 0; j<i; j++){
      bitstring[j] = 1;
    }
    do {
      if(check_bitstring(bitstring)){ 
        satisfying_assignments.push_back(bitstring);
      }
    } while(std::prev_permutation(bitstring.begin(), bitstring.end()));
  }
}

/** checks whether a bitstring solves a CNF formula
    @param bitstring the candidate bit string
    @return true if the bitstring satisfies the formula, false otw */
bool CNFFormula::check_bitstring(std::vector<short> & bitstring) const {
  for(const auto & clause : clauses){
    if(!clause.check_bitstring(bitstring)){
      return false;
    }
  }
  return true;
}

/** adds a clause to the formula
    @param clause the clause to add */

void CNFFormula::add_clause(const CNFClause & clause){
  clauses.push_back(clause);
}
