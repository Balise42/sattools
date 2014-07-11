#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <set>

#include "permstats.h"
#include "structs.h"
#include "cnfclause.h"
#include "assignment.h"

PermStats::PermStats(CNFClause c, unsigned int variable):PpzRunStats(),permsets(std::map<Assignment,std::set<std::vector<int> > >()),statsclause(c),variable(variable){
}

void PermStats::add_perm_to_assg(Assignment & assg, const std::vector<int> & perm){
  boost::lock_guard<boost::mutex> guard(mutex_assig);
  if(permsets.count(assg) == 0){
    permsets[assg] = std::set<std::vector<int> >();
  }
  permsets[assg].insert(perm);
}

void PermStats::set_nf_to_perm(Assignment & assg, bool nf){
  boost::lock_guard<boost::mutex> guard(mutex_nf);
  if(numnf.count(assg) == 0){
    numnf[assg] = 0;
  }
  if(nf){
    numnf[assg]++;
  }
}

unsigned int PermStats::get_stats_lit_clause(const Assignment & assg) const {
  int total = 0;
  if(permsets.count(assg) == 0){
    return 0;
  }
  for(std::vector<int> perm : permsets.at(assg)){
    bool valid = true;
    std::vector<int>::iterator pos = std::find(perm.begin(),perm.end(),variable-1);
    for(const auto lit : statsclause){
      if(lit.variable == variable-1){
        continue;
      }
      else if(std::find(perm.begin(),perm.end(),lit.variable) > pos){
        valid = false;
        break;
      }
    }
    if(valid){
      total++;
    }
  }
  return total;
}

unsigned int PermStats::get_variable(){
  return variable;
}

std::ostream & operator<<(std::ostream & out, const PermStats & stats){
  out << * (dynamic_cast<const PpzRunStats * >(&stats));
  for(const auto & el : stats.permsets){
    for(const auto & lit : el.first){
      out << lit;
    }
    out << std::endl;
    for(const auto & perm : el.second){
      for(const auto & lit : perm){
         out << lit+1;
      }
      out << std::endl;
    }
    out << ":\n";
    std::vector<int> spec(3);
    out << "Stats for var " << stats.variable << " in clause " << stats.statsclause << ": " << stats.get_stats_lit_clause(el.first) << " / " << el.second.size() << std::endl;
    out << "Var " << stats.variable << "is non-frozen in " << stats.numnf.at(el.first) << " / " << el.second.size() << "permutations" << std::endl;

    out << std::endl;
  }
  return out;
}
