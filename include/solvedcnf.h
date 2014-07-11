#include <vector>
#include <iostream>
#include "cnfformula.h"
#include "structs.h"
#include "assignment.h"

/** A solved CNF formula */
class SolvedCNF{
  private:
    /** The CNF formula */
    CNFFormula * f;
    /** Satisfying assignments to the formula */
    std::vector<Assignment> satisfying_assignments;
    /** solves a CNF formula by brute force - going to all 2^n assignments.
      @param partial a partial assignment
      @param assignments an empty vector at the beginning of the execution, the satisfying assignments at the end of the execution
    */
    void bruteforce_solve_sat(std::vector<Assignment> & assignments, Assignment partial = Assignment(0)) const;

  public:
    SolvedCNF(const CNFFormula & f);
    SolvedCNF(const SolvedCNF & f);
    ~SolvedCNF();
    friend std::ostream& operator<<(std::ostream& out, const SolvedCNF & formula);

    /** checks whether a variable is frozen, i.e. if it has the same value in all the satisfying assignments
    @return true if the variable is frozen, false otw */
    bool is_frozen(int variable, Assignment partial) const;

    /** @return true if the formula has (precomputed) satisfying assignments, false otherwise */
    bool has_satisfying_assignments() const {return satisfying_assignments.size() > 0;}

    /** @return the set of computed satisfying assignments */
    std::vector<Assignment> get_satisfying_assignments() const {return satisfying_assignments;}
};
