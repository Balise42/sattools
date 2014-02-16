#ifndef CNFFORMULA_H
#define CNFFORMULA_H 1

#include <iostream>
#include <vector>
#include "cnfclause.h"

/** represents a CNF formula */
class CNFFormula{
  private:
    /** number of variables */
    unsigned int n;
    /** max number of literals in a clause ("k-SAT") */
    unsigned int k;
    /** clauses of the formula */
    std::vector<CNFClause> clauses;

  public:
    /** creates an empty formula */
    CNFFormula();

    /** creates a CNF formula with the given clauses and assignments, with default empty clause vector */
    CNFFormula(unsigned int n, int k, const std::vector<CNFClause> & clauses = std::vector<CNFClause>(0));

    /** does the assignment passed in parameter, does not modify the current formula 
    @param assg the assignment to make - 0 or 1 to corresponding variables, -1 for unassigned variables
    @return a new CNFFormula with the assignment made */
    CNFFormula make_assignment(const assignment & assg) const;
    
    /** checks whether a bitstring solves a CNF formula
    @param bitstring the candidate bit string
    @return true if the bitstring satisfies the formula, false otw */
    bool check_bitstring(const std::vector<short> & bitstring) const;

    /** adds a clause to the formula
    @param clause the clause to add */
    void add_clause(const CNFClause & clause);

    /** pretty printer for the formula */
    friend std::ostream& operator<<(std::ostream& out, const CNFFormula & formula);

    /** accessor for private field n (number of variables) */
    unsigned int get_n() const;

    /** accessor for private field k (arity) */
    unsigned int get_k() const;

    /** checks whether a formula is trivially unsatisfiable
    @return true if the formula contains the empty clause, false otherwise */
    bool is_unsat() const;

    /** @param the variable for which we want to get a forced value
    @return 0 or 1 if the variable is forced to 0 or 1, -1 if it is not forced */
    short get_forced_value(unsigned int variable) const;

    /** @return the number of clauses of the formula */
    int get_m() const;

    /** save the formula to file in DIMACS format*/
    void save(std::string filename);

    /** iterator over the clauses of the formula */
    typedef std::vector<CNFClause>::iterator iterator;
    /** const iterator over the clauses of the formula */
    typedef std::vector<CNFClause>::const_iterator const_iterator;
    /** begin iterator over the clauses of the formula */
    iterator begin();
    /** begin iterator over the clauses of the formula */
    const_iterator begin() const;
    /** end iterator over the clauses of the formula */
    iterator end();
    /** end iterator over the clauses of the formula */
    const_iterator end() const;
};

#endif
