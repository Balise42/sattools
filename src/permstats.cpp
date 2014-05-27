#include <iostream>
#include <map>
#include <vector>
#include <set>

#include "permstats.h"
#include "structs.h"

PermStats::PermStats():permsets(std::map<assignment,std::set<std::vector<int> > >()){
}

void PermStats::add_perm_to_assg(assignment & assg, std::vector<int> & perm){
  if(permsets.count(assg) == 0){
    permsets[assg] = std::set<std::vector<int> >();
  }
  permsets[assg].insert(perm);
}

std::ostream & operator<<(std::ostream & out, const PermStats & stats){
  for(const auto & el : stats.permsets){
    for(const auto & lit : el.first){
      out << lit;
    }
    out << ":\n";
    for(const auto & perm : el.second){
      for(const auto & var : perm){
        out << var;
      }
      out << std::endl;
    }
    out << std::endl;
  }
  return out;
}
