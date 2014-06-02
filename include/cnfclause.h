#ifndef CLAUSE_H
#define CLAUSE_H 1

#include <vector>
#include <iostream>
#include <fstream>
#include "structs.h"
#include "assignment.h"

/** CNF clause (disjunction of literals) */
class CNFClause{
  private:
    std::vector<literal> clause; //!< a clause is a vector of literals 

  public:
    /** creates an empty clause */
    CNFClause();

    /** creates a clause from a vector of literals
    @param clause the vector of literals */
    CNFClause(const std::vector<literal> & clause);

    /** creates a clause from a clause specification (from DIMACS format) 
     @param vector of integers; value of integer is the variable, sign of the integer
     is value of the literal in the clause */
    CNFClause(const std::vector<int> & clausespec);

    /** add a literal to the clause
    @param l the literal to add
    @returns false if the variable is already in the clause, true otherwise */
    bool add_literal(literal l);

    /** checks whether a given bitstring/assignment satisfies the clause\n
    note: if the bitstring is "too short", we assume that it is a partial
    assignment and that a clause containing out-of-bounds variables is
    satisfied.
    @param the bitstring to check
    @return true if the bitstring satisfies the clause, false otw*/
    bool check_bitstring(const Assignment & bitstring) const;

    /** saves a clause to file (DIMACS format) */
    void save(std::ofstream & file) const;
    
    /** pretty print of a clause */
    friend std::ostream& operator<<(std::ostream& out, const CNFClause & clause);

    /** iterator for the literals of the clause */
    typedef std::vector<literal>::iterator iterator;

    /** const iterator for the literals of the clause */
    typedef std::vector<literal>::const_iterator const_iterator;

    /** begin iterator over the literals of the clause */
    iterator begin();

    /** begin iterator over the literals of the clause */
    const_iterator begin() const;

    /** end iterator over the literals of the clause */
    iterator end();

    /** end iterator over the literals of the clause */
    const_iterator end() const;

    /** @return the "pos"th literal of the clause */
    literal getliteral(int pos) const;

    /** @return the number of variables in the clause */
    unsigned int size() const;
};

#endif
