#ifndef PERMSTATS_H
#define PERMSTATS_H 1

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "structs.h"
#include "cnfclause.h"
#include "ppzrunstats.h"
#include "assignment.h"

class PermStats : public PpzRunStats {
  private:
    std::map<Assignment, std::set<std::vector<int> > > permsets;
    CNFClause statsclause;
    unsigned int variable;

  public:
    /** default constructor */
    PermStats(CNFClause c, unsigned int variable);
    /** add a permutation to an assignment */
    void add_perm_to_assg(Assignment & assg, const std::vector<int> & perm);
    /** get stats for "last in clause" for a clause and a lit for a given assignment */
    unsigned int get_stats_lit_clause(const Assignment & assg) const;
    /** prettyprinter */
    friend std::ostream & operator<<(std::ostream & out, const PermStats & stats);
};

#endif
