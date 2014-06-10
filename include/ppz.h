#ifndef PPZ_H
#define PPZ_H 1

#include <vector>
#include <set>
#include <iostream>
#include "cnfformula.h"
#include "structs.h"
#include "ppzrunstats.h"

/** This is a derandomized PPZ algorithm, and by derandomized I mean it goes through
    ALL the permutations of the variables and through ALL the 0/1 bits when they are
    not forced. Hence this is a VERY inefficient algorithm (worst case O(n!2^n) on 
    empty formula!). */
class Ppz{
  private:
    /** the formula that we want to process with the algorithm */
    CNFFormula formula;
    /** satisfying assignments at the end of the algorithm */
    std::set<Assignment> assignments;

    /** Executes a permutation. For every variable in the order of the permutation, if
     it is forced, set it to its value. If it is not, if the oracle is on and the variable is
     non-frozen, set it to 0. In the other cases, set it to the corresponding bit from the
     "randombits".
     @param permutation a permutation of variables
     @param randombits a string of bits for "guessing" variables if they are not forced
     @param oracle whether the oracle is on or not 
     @return assignment a satisfying assignment or an empty vector if the run fails */
    Assignment execute_bitstring(const std::vector<int> & permutation, const std::vector<short> & randombits, unsigned int & forced, bool oracle);

    void execute_permutation(const std::vector<int> & permutation, bool oracle, PpzRunStats * stats);
  public:
    /** default constructor */
    Ppz(CNFFormula & formula);
    /** destructor */
    ~Ppz();
    /** runs ppz up to "limit" times on random permutation and random bitstring
     @param limit the maximum number of trials
     @return a satisfying assignment or an empty vector if the algorithm fails */
    Assignment random_solve_ppz(double limit);
    /** runs PPZ over all possible permutations and all possible bitstrings
      @param oracle true if we use the oracle, false otw
      */
    void full_solve_ppz(PpzRunStats & stats, bool oracle = false);
    /** prettyprint of the stats*/
};

#endif

