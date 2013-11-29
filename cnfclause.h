#ifndef CLAUSE_H
#define CLAUSE_H 1

#include <vector>
#include <iostream>
#include "structs.h"

/** CNF clause (disjunction of literals) */
class CNFClause{
  private:
    std::vector<literal> clause; //!< a clause is a vector of literals 

  public:
    CNFClause();
    CNFClause(const std::vector<literal> & clause);
    CNFClause(const std::vector<int> & clausespec);
    bool add_literal(literal l);
    bool check_bitstring(const std::vector<short> & bitstring) const;
    friend std::ostream& operator<<(std::ostream& out, const CNFClause & clause);

    typedef std::vector<literal>::iterator iterator;
    typedef std::vector<literal>::const_iterator const_iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    literal getliteral(int pos) const;
    unsigned int size() const;
};

#endif
