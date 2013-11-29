#ifndef PPZ_H
#define PPZ_H 1

#include <vector>
#include <iostream>
#include "cnfformula.h"
#include "structs.h"
#include <set>

/** This is a derandomized PPZ algorithm, and by derandomized I mean it goes through
    ALL the permutations of the variables and through ALL the 0/1 bits when they are
    not forced. Hence this is a VERY inefficient algorithm (worst case O(n!2^n) on 
    empty formula!). */
class Ppz{
  private:
    /** the formula that we want to process with the algorithm */
    CNFFormula * formula;
    /** satisfying assignments at the end of the algorithm without oracle */
    std::set<assignment> assignments;
    /** satisfying assignments at the end of the algorithm with oracle */
    std::set<assignment> assignments_o;
    /** counts all the cases executed by ppz */
    int all_cases;
    /** counts all cases that actually return a satisfying assignment */
    int satisfying_cases;
    /** counts all the cases executed by ppz with oracle */
    int all_cases_o;
    /** counts the satisfying cases for ppz with oracle */
    int satisfying_cases_o;

    assignment execute_permutation(const std::vector<int> & permutation, const std::vector<short> & randombits, bool oracle);

  public:
    Ppz(CNFFormula * formula);
    assignment random_solve_ppz(double limit);
    void full_solve_ppz(bool oracle = false);
    friend std::ostream & operator<<(std::ostream & out, const Ppz & ppz);
};

#endif

