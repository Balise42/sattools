#ifndef CLAUSE_H
#define CLAUSE_H 1

#include <vector>
#include "structs.h"

/** CNF clause (disjunction of literals) */
class CNFClause{
  private:
    std::vector<literal> clause; //!< a clause is a vector of literals 

  public:
    CNFClause();
    CNFClause(const std::vector<literal> & clause);
    bool add_literal(literal l);
    bool check_bitstring(const std::vector<short> & bitstring) const;
};

#endif
