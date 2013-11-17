#ifndef CNFFORMULA_H
#define CNFFORMULA_H 1

#include <vector>
#include "cnfclause.h"

/** represents a CNF formula */
class CNFFormula{
  private:
    /** number of variables */
    int n;
    /** max number of literals in a clause ("k-SAT") */
    int k;
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
    CNFFormula(int n, int k, const std::vector<CNFClause> & clauses = std::vector<CNFClause>(0), const std::vector<assignment> assignments  = std::vector<assignment>(0));
    void bruteforce_solve_sat();
    bool check_bitstring(const std::vector<short> & bitstring) const;
    void add_clause(const CNFClause & clause);
};

#endif
