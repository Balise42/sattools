#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "cnfformula.h"
#include "structs.h"

/** creates a CNF formula with the given clauses and assignments, with default empty clause and empty assignment vectors */
CNFFormula::CNFFormula(unsigned int n, int k, const std::vector<CNFClause> & clauses, const std::vector<assignment> assignments):n(n), k(k), clauses(clauses),unchecked_assignments(assignments){
}

/** solves a CNF formula by brute force - going to all 2^n assignments.
    assigns satisfying_assignments to contain the satisfying assignments
    and sets was_solved to true. if was_solved is already set to true then we do
    not re-solve.*/
void CNFFormula::bruteforce_solve_sat(std::vector<short> partial){
  // we don't want to re-solve if it has already been solved
  if(was_solved){
    return;
  }

  if(partial.size() == 0){
    partial = std::vector<short>(n, -1);
  }

  std::vector<short> bitstring;
  //we enumerate all the bitstrings by taking all permutations of strings
  //that have i bits to 1
  for(unsigned int i = 0; i<=n; i++){
    bitstring = std::vector<short>(n, 0);
    for(unsigned int j = 0; j<i; j++){
      bitstring[j] = 1;
    }
    do {
      std::vector<short> bitstringwithpartial(n);
      for(int j = 0; j<n; j++){
        if(partial[j] != -1){
          bitstringwithpartial[j] = partial[j];
        }
        else{
          bitstringwithpartial[j] = bitstring[j];
        }
      } 
      if(check_bitstring(bitstringwithpartial)){ 
        satisfying_assignments.push_back(bitstringwithpartial);
      }
    } while(std::prev_permutation(bitstring.begin(), bitstring.end()));
  }
  was_solved = true;
}

/** checks whether a bitstring solves a CNF formula
    @param bitstring the candidate bit string
    @return true if the bitstring satisfies the formula, false otw */
bool CNFFormula::check_bitstring(const std::vector<short> & bitstring) const {
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

std::ostream& operator<<(std::ostream& out, const CNFFormula & formula){
  for(const auto & clause : formula.clauses){
    for(const auto & literal : clause){
      if(literal.value == 0){
        out << "~";
      }
      out << "x" << literal.variable+1 << ",";
    }
    out << std::endl;
  }
  if(formula.was_solved){
    out << "Assignments:" << std::endl;
    for(const auto & assig:formula.satisfying_assignments){
      int var = 1;
      for(const auto & lit : assig){
        out << "x" << var << "=" << lit << ",";
        var++;
      }
      out << std::endl;
    }
  }
  return out;
}

/** does the assignment passed in parameter, does not modify the current formula 
    @param assg the assignment to make - 0 or 1 to corresponding variables, -1 for unassigned variables
    @ return a new CNFFormula with the assignment made */
CNFFormula CNFFormula::make_assignment(const assignment & assg) const {
//  assert(assg.size() == n);
  CNFFormula formula(n, k);
  for(const auto & clause : clauses){
    bool addit = true;
    for(const auto & lit : clause){
      //if the variable is not set in the assignment then nothing changes
      if(assg[lit.variable] == -1){
        continue;
      }
      // if a literal has the right value then the clause is satisfied and we do not add it
      if(lit.value == assg[lit.variable]){
        addit = false;
        continue;
      }
      //otherwise we create a new clause without the (unsatisfied) literal and we add it
      //(but not the original clause)
      else{
        CNFClause newclause;
        for(auto lit1 : clause){
          if(lit1.variable != lit.variable){
            newclause.add_literal(lit1);
          }
        }
        formula.add_clause(newclause);
        addit = false;
      }
    }
    //if we still need to add that clause then we do it
    if(addit){
      formula.add_clause(clause);
    }
  }
  return formula;
}

unsigned int CNFFormula::get_n() const{
  return n;
}

bool CNFFormula::is_unsat() const{
  for(auto const & clause : clauses){
    if(clause.size() == 0){
      return true;
    }
  }
  return false;
}

int CNFFormula::get_forced_value(int variable) const{
  for(auto const & clause : clauses){
    if(clause.size() == 1){
      if(clause.getliteral(0).variable == variable){
        return clause.getliteral(0).value;
      }
    }
  }
  return -1;
}

int CNFFormula::get_m() const{
  return clauses.size();
}

/** bruteforce solves to check if a variable is frozen. quite ugly,
    but since PPZ is slow as a tetraplegic turtle anyway... */
bool CNFFormula::is_frozen(int variable, std::vector<short> partial){
  bruteforce_solve_sat(partial);
  //if there is no satisfying assignment, the variable has the same value in all sat. assg.
  if(satisfying_assignments.size() == 0){
    return true;
  }
  short value = satisfying_assignments[0][variable];
  for(auto const & assig : satisfying_assignments){
    if(assig[variable] != value){
      return false;
    }
  }
  return true;
}
