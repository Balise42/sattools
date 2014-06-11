#ifndef PERMSTATS_H
#define PERMSTATS_H 1

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <boost/thread.hpp>
#include "structs.h"
#include "cnfclause.h"
#include "ppzrunstats.h"
#include "assignment.h"

class PermStats : public PpzRunStats {
  private:
    std::map<Assignment, std::set<std::vector<int> > > permsets;
    std::map<Assignment, unsigned long> numnf;
    CNFClause statsclause;
    unsigned int variable;
    boost::mutex mutex_assig;
    boost::mutex mutex_nf;

  public:
    /** default constructor */
    PermStats(CNFClause c, unsigned int variable);
    /** add a permutation to an assignment */
    void add_perm_to_assg(Assignment & assg, const std::vector<int> & perm);
    void set_nf_to_perm(Assignment & assg, bool nf);

    /** get stats for "last in clause" for a clause and a lit for a given assignment */
    unsigned int get_stats_lit_clause(const Assignment & assg) const;

    unsigned int get_variable();
    /** prettyprinter */
    friend std::ostream & operator<<(std::ostream & out, const PermStats & stats);
};

#endif
