/* Basic structures: Class for CNF clauses (disjunction of literals) */
#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "cnfclause.h"
#include "assignment.h"

CNFClause::CNFClause() : clause(std::vector<literal>(0)) {
}

CNFClause::CNFClause(const std::vector<literal> & clause) : clause(clause){
}

CNFClause::CNFClause(const std::vector<int> & clausespec) :  clause(std::vector<literal>(0)){
  literal l;
  // we loop over the vector and add the literals one by one to the clause according to the spec
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

bool CNFClause::add_literal(literal l){
  for(auto lit : clause){
    if(lit.variable == l.variable){
      return false;
    }
  }
  clause.push_back(l);
  return true;
}

bool CNFClause::check_bitstring(const Assignment & bitstring) const {
  bool ok = false;
  // we check whether an assignment is compatible with the clause literal by literal
  for(const auto & lit : clause){
    ok = ok || (lit.variable >= bitstring.size()) || (lit.value == bitstring[lit.variable]);
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

literal CNFClause::getliteral(int pos) const{
  return clause.at(pos);
}

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

bool operator<(literal a, literal b){
  return (std::make_pair(a.variable, a.value) < std::make_pair(b.variable,b.value));
}

bool operator==(literal a, literal b){
  return(a.variable==b.variable && a.value == b.value);
}

bool operator==(CNFClause a, CNFClause b){
  std::vector<literal> ca = a.clause;
  std::sort(ca.begin(), ca.end());
  std::vector<literal> cb = b.clause;
  std::sort(cb.begin(),cb.end());
  return(ca == cb);
}
