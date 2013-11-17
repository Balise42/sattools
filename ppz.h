#ifndef PPZ_H
#define PPZ_H 1

#include <vector>
#include <iostream>
#include "cnfformula.h"
#include "structs.h"

/** This is a derandomized PPZ algorithm, and by derandomized I mean it goes through
    ALL the permutations of the variables and through ALL the 0/1 bits when they are
    not forced. Hence this is a VERY inefficient algorithm (worst case O(n!2^n) on 
    empty formula!). */
class Ppz{
  private:
    /** the formula that we want to process with the algorithm */
    CNFFormula * formula;
    /** satisfying assignments at the end of the algorithm */
    std::vector<assignment> assignments;
    /** counts all the cases executed by ppz */
    int all_cases;
    /** counts all cases that actually return a satisfying assignment */
    int satisfying_cases;

    assignment execute_permutation(const std::vector<int> & permutation, const std::vector<short> & randombits);

  public:
    Ppz(CNFFormula * formula);
    void solve_ppz();
    friend std::ostream & operator<<(std::ostream & out, const Ppz & ppz);
};

#endif

