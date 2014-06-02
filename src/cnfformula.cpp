/* CNF formula class. */
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cassert>
#include "cnfformula.h"
#include "assignment.h"
#include "structs.h"

CNFFormula::CNFFormula(unsigned int n, int k, const std::vector<CNFClause> & clauses):n(n), k(k), clauses(clauses){
}

CNFFormula::CNFFormula(){}

bool CNFFormula::check_bitstring(const Assignment & bitstring) const {
  //we just check if it satisfies all clauses
  for(const auto & clause : clauses){
    if(!clause.check_bitstring(bitstring)){
      return false;
    }
  }
  return true;
}

void CNFFormula::add_clause(const CNFClause & clause){
  clauses.push_back(clause);
}

std::ostream& operator<<(std::ostream& out, const CNFFormula & formula){
  for(const auto & clause : formula.clauses){
    out << clause;
  }
  return out;
}

CNFFormula CNFFormula::make_assignment(const Assignment & assg) const {
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

unsigned int CNFFormula::get_k() const{
  return k;
}

bool CNFFormula::is_unsat() const{
  for(auto const & clause : clauses){
    if(clause.size() == 0){
      return true;
    }
  }
  return false;
}

short CNFFormula::get_forced_value(unsigned int variable) const{
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

CNFFormula::iterator CNFFormula::begin(){
  return clauses.begin();
}

CNFFormula::const_iterator CNFFormula::begin() const{
  return clauses.begin();
}

CNFFormula::iterator CNFFormula::end(){
  return clauses.end();
}

CNFFormula::const_iterator CNFFormula::end() const{
  return clauses.end();
}

void CNFFormula::save(std::string filename) const{
  std::ofstream file;
  file.open(filename, std::ios::out | std::ios::trunc);
  if(!file.is_open()){
    return;
  }
  // header of the file
  file << "p cnf " << n << " " << get_m() << std::endl;
  //print all clauses one by one
  for(const auto & clause : clauses){
    clause.save(file);
  }
  file.close();
}
