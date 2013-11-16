#include <vector>
#include "clause.h"

///creates an empty clause
CNFClause::CNFClause() : clause(std::vector<literal>(0)) {
}

///creates a clause from a vector of literals
///@param clause the vector of literals
CNFClause::CNFClause(const std::vector<literal> & clause) : clause(clause){
}

///add a literal to the clause
///@param l the literal to add
///@returns false if the variable is already in the clause, true otherwise
bool CNFClause::add_literal(literal l){
  for(auto lit : clause){
    if(lit.variable == l.variable){
      return false;
    }
  }
  clause.push_back(l);
  return true;
}
