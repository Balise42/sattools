#include <vector>
#include <algorithm>
#include <iostream>

#include "structs.h"
#include "ppz.h"

Ppz::Ppz(CNFFormula * formula):formula(formula),assignments(std::vector<assignment>(0)),all_cases(0),satisfying_cases(0){
}

void Ppz::solve_ppz(){
  all_cases = 0;
  satisfying_cases = 0;
  unsigned int n = formula->get_n();
  std::vector<int> permutation(n, 0);
  for(int i = 0; i<n; i++){
    permutation[i] = i;
  }

  do{
    std::vector<short> bitstring;
    //we enumerate all the bitstrings by taking all permutations of strings
    //that have i bits to 1
    for(unsigned int i = 0; i<= n; i++){
      bitstring = std::vector<short>(n, 0);
      for(unsigned int j = 0; j<i; j++){
        bitstring[j] = 1;
      }
      do{
        all_cases++;
        assignment assg = execute_permutation(permutation, bitstring);
        if(assg.size() != 0 && formula->check_bitstring(assg)){
          satisfying_cases++;
          assignments.push_back(assg);
        }
      } while(std::prev_permutation(bitstring.begin(), bitstring.end()));
    }
  } while(std::next_permutation(permutation.begin(), permutation.end()));
}

assignment Ppz::execute_permutation(const std::vector<int> & permutation, const std::vector<short> & randombits){
  unsigned n = formula->get_n();
  assignment assg(n, -1);
  CNFFormula F = *formula;
  for(const auto & variable : permutation){
    assg[variable] = F.get_forced_value(variable);
    if(assg[variable] == -1){
      assg[variable] = randombits[variable];
    }
    F = F.make_assignment(assg);
    if(F.get_m() == 0){
      return assg;
    }
    if(F.is_unsat()){
      return std::vector<short>(0);
    }
  }
  return assg;
}

std::ostream & operator<<(std::ostream & out, const Ppz & ppz){
  for(const auto & assignment : ppz.assignments){
    out << "Assignment:" << std::endl;
    int var = 1;
    for(const auto & lit : assignment){
      out << "x" << var << "=" << lit << ",";
      var++;
    }
    out << std::endl;
  }
  out << "Total # of tries: " << ppz.all_cases << std::endl;
  out << "# of working tries: " << ppz.satisfying_cases << std::endl;
  return out;
}
