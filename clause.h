#include <vector>
#include "literal.h"

/** CNF clause (disjunction of literals) */
class CNFClause{
  private:
    std::vector<literal> clause; //!< a clause is a vector of literals 

  public:
    CNFClause();
    
    CNFClause(const std::vector<literal> & clause);

    bool add_literal(literal l);
};
