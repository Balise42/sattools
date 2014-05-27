#ifndef PERMSTATS_H
#define PERMSTATS_H 1

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "structs.h"

class PermStats {
  private:
    std::map<assignment, std::set<std::vector<int> > > permsets;

  public:
    /** default constructor */
    PermStats();
    /** add a permutation to an assignment */
    void add_perm_to_assg(assignment & assg, std::vector<int> & perm);
    /** prettyprinter */
    friend std::ostream & operator<<(std::ostream & out, const PermStats & stats);
};

#endif
