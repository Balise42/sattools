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
    CNFFormula * formula;
    /** satisfying assignments at the end of the algorithm without oracle */
    std::set<assignment> assignments;
    /** satisfying assignments at the end of the algorithm with oracle */
    std::set<assignment> assignments_o;
    /** whether we're currently dealing with assignmets or assignmets_o */
    std::set<assignment> * currassg;
    /** stats for PPZ run */
    PpzRunStats * stats;
    /** stats for PPZ run with oracle */
    PpzRunStats * stats_o;
    /** whether we're currently dealing with stats or stats_o */
    PpzRunStats * currstats;

    assignment execute_permutation(const std::vector<int> & permutation, const std::vector<short> & randombits, bool oracle);

  public:
    Ppz(CNFFormula * formula);
    ~Ppz();
    assignment random_solve_ppz(double limit);
    void full_solve_ppz(bool oracle = false);
    friend std::ostream & operator<<(std::ostream & out, const Ppz & ppz);
};

#endif

