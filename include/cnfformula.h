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
    /** indicates if the bruteforce_solve_sat method has been executed on the formula */
    bool was_solved;
    /** guessed, unchecked assignments given by the user or the generator.
        these give no guarantee that they are correct or complete. */
    std::vector<assignment> unchecked_assignments;
    /** assignments computed by bruteforce_solve_sat.
        if was_solved is true, guaranteed to be correct and complete */
    std::vector<assignment> satisfying_assignments;

  public:
    /** creates an empty formula */
    CNFFormula();

    /** creates a CNF formula with the given clauses and assignments, with default empty clause and empty assignment vectors */
    CNFFormula(unsigned int n, int k, const std::vector<CNFClause> & clauses = std::vector<CNFClause>(0), const std::vector<assignment> assignments  = std::vector<assignment>(0));

    /** solves a CNF formula by brute force - going to all 2^n assignments.
    assigns satisfying_assignments to contain the satisfying assignments
    and sets was_solved to true. if was_solved is already set to true then we do
    not re-solve.*/ 
    void bruteforce_solve_sat(std::vector<short> partial = std::vector<short>(0));

    /** checks whether a bitstring solves a CNF formula
    @param bitstring the candidate bit string
    @return true if the bitstring satisfies the formula, false otw */
    bool check_bitstring(const std::vector<short> & bitstring) const;

    /** adds a clause to the formula
    @param clause the clause to add */
    void add_clause(const CNFClause & clause);

    /** pretty printer for the formula */
    friend std::ostream& operator<<(std::ostream& out, const CNFFormula & formula);

    /** does the assignment passed in parameter, does not modify the current formula 
    @param assg the assignment to make - 0 or 1 to corresponding variables, -1 for unassigned variables
    @return a new CNFFormula with the assignment made */
    CNFFormula make_assignment(const assignment & assg) const;

    /** accessor for private field n (number of variables) */
    unsigned int get_n() const;

    /** checks whether a formula is trivially unsatisfiable
    @return true if the formula contains the empty clause, false otherwise */
    bool is_unsat() const;

    /** @param the variable for which we want to get a forced value
    @return 0 or 1 if the variable is forced to 0 or 1, -1 if it is not forced */
    short get_forced_value(unsigned int variable) const;

    /** @return the number of clauses of the formula */
    int get_m() const;

    /** checks whether a variable is frozen, i.e. if it has the same value in all the satisfying assignments
    @return true if the variable is frozen, false otw */
    bool is_frozen(int variable, std::vector<short> partial);

    /** @return true if the formula has (precomputed) satisfying assignments, false otherwise */
    bool has_satisfying_assignments(){return satisfying_assignments.size() > 0;}

    /** @return true if the formula was already solved by bruteforce, false otw */
    bool is_solved(){return was_solved;}

    /** @return the set of computed satisfying assignments */
    std::vector<assignment> get_satisfying_assignments(){return satisfying_assignments;}

    /** save the formula to file in DIMACS format*/
    void save(std::string filename);

    typedef std::vector<CNFClause>::iterator iterator;
    typedef std::vector<CNFClause>::const_iterator const_iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};

#endif
