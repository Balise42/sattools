#include <iostream>
#include <climits>
#include "ppzrunstats.h"


PpzRunStats::PpzRunStats():all_cases(0),satisfying_cases(0),forced_a(0),maxforced_a(0),minforced_a(UINT_MAX),forced_s(0),maxforced_s(0),minforced_s(UINT_MAX),forced_u(0),maxforced_u(0),minforced_u(UINT_MAX),tmpforced(0){
}

void PpzRunStats::updateminmax(unsigned int tmp, unsigned int & maxforced, unsigned int & minforced, unsigned int & total){
  total += tmp;
  if(tmp > maxforced){
    maxforced = tmp;
  }
  if(tmp < minforced){
    minforced = tmp;
  }
}

void PpzRunStats::tally_stats(bool satisfying){
  all_cases++;
  updateminmax(tmpforced, maxforced_a, minforced_a, forced_a);
  if(satisfying){
    satisfying_cases++;
    updateminmax(tmpforced, maxforced_s, minforced_s, forced_s);
  }
  else{
    updateminmax(tmpforced, maxforced_u, minforced_u, forced_u);
  }
}

std::ostream & operator<<(std::ostream & out, const PpzRunStats & s){
  out << "Total # of tries: " << s.all_cases << std::endl;
  out << "# of working tries: " << s.satisfying_cases << std::endl;
  out << "Total # of forced variables (all results): " << s.forced_a << std::endl;
  out << "Avg/Max/Min # of forced variables (all results): " << (double)s.forced_a/(double) s.all_cases << "/" << s.maxforced_a << "/" << s.minforced_a << std::endl;
  out << "Total # of forced variables (sat. assignments): " << s.forced_s << std::endl;
  out << "Avg/Max/Min # of forced variables (sat. assignments): " << (double)s.forced_s/(double) s.satisfying_cases << "/" << s.maxforced_s << "/" << s.minforced_s << std::endl;
  out << "Total # of forced variables (unsat. cases): " << s.forced_u << std::endl;
  out << "Avg/Max/Min # of forced variables (unsat. cases): " << (double)s.forced_u/(double) (s.all_cases - s.satisfying_cases) << "/" << s.maxforced_u << "/" << s.minforced_u << std::endl;
  return out;
}
