#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "cnfclause.h"

///creates an empty clause
CNFClause::CNFClause() : clause(std::vector<literal>(0)) {
}

///creates a clause from a vector of literals
///@param clause the vector of literals
CNFClause::CNFClause(const std::vector<literal> & clause) : clause(clause){
}

CNFClause::CNFClause(const std::vector<int> & clausespec) :  clause(std::vector<literal>(0)){
  literal l;
  for(const auto & litspec : clausespec){
    if(litspec == 0){
      return;
    }
    l.variable = abs(litspec)-1;
    if(litspec > 0){
      l.value = 1;
    }
    else{
      l.value = 0;
    }
    clause.push_back(l);
  }
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

///checks whether a given bitstring/assignment satisfies the clause\n
///note: if the bitstring is "too short", we assume that it is a partial
///assignment and that a clause containing out-of-bounds variables is
///satisfied.
///@param the bitstring to check
///@return true if the bitstring satisfies the clause, false otw
bool CNFClause::check_bitstring(const std::vector<short> & bitstring) const {
  bool ok = false;
  for(const auto & lit : clause){
    ok = ok || (lit.variable >= bitstring.size()) || (lit.value == bitstring[lit.variable]);
  }
  return ok;
}

/** begin iterator over the literals of the clause */
CNFClause::iterator CNFClause::begin(){
  return clause.begin();
}

/** begin iterator over the literals of the clause */
CNFClause::const_iterator CNFClause::begin() const{
  return clause.begin();
}

/** end iterator over the literals of the clause */
CNFClause::iterator CNFClause::end(){
  return clause.end();
}

/** end iterator over the literals of the clause */
CNFClause::const_iterator CNFClause::end() const{
  return clause.end();
}

/** @return the "pos"th literal of the clause */
literal CNFClause::getliteral(int pos) const{
  return clause.at(pos);
}

/** @return the number of variables in the clause */
unsigned int CNFClause::size() const{
  return clause.size();
}

std::ostream& operator<<(std::ostream& out, const CNFClause & clause){
  for(const auto & literal : clause){
    if(literal.value == 0){
      out << "~";
    }
  out << "x" << literal.variable+1 << ",";
  }
  out << std::endl;
  return out;
}

void CNFClause::save(std::ofstream & file) const{
  if(file.is_open()){
    for(const auto & lit : clause){
      if(lit.value == 0){
        file << "-";
      }
      file << lit.variable+1 << " ";
    }
    file << "0" << std::endl;
  }
}
