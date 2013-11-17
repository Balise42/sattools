#include <vector>
#include "cnfclause.h"

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

///checks whether a given bitstring/assignment satisfies the clause
///@param the bitstring to check
///@return true if the bitstring satisfies the clause, false otw
bool CNFClause::check_bitstring(const std::vector<short> & bitstring) const {
  bool ok = false;
  for(const auto & lit : clause){
    ok = ok || (lit.value == bitstring[lit.variable]);
  }
  return ok;
}

CNFClause::iterator CNFClause::begin(){
  return clause.begin();
}

CNFClause::const_iterator CNFClause::begin() const{
  return clause.begin();
}

CNFClause::iterator CNFClause::end(){
  return clause.end();
}

CNFClause::const_iterator CNFClause::end() const{
  return clause.end();
}
