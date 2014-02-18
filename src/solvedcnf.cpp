/* Basic structures: a solved CNF formula (by bruteforce) - also allows checking for frozen variables. */
#include <algorithm>
#include <vector>
#include <iostream>
#include "solvedcnf.h"
#include "cnfformula.h"

SolvedCNF::SolvedCNF(const CNFFormula & f):f(new CNFFormula(f)),satisfying_assignments(std::vector<assignment>(0)){
  bruteforce_solve_sat(satisfying_assignments);
}

SolvedCNF::~SolvedCNF(){
  delete f;
}

void SolvedCNF::bruteforce_solve_sat(std::vector<assignment> & assignments, std::vector<short> partial) const {
  unsigned int n = f->get_n();
  if(partial.size() == 0){
    partial = std::vector<short>(n, -1);
  }

  std::vector<short> bitstring;
  //we enumerate all the bitstrings by taking all permutations of strings
  //that have i bits to 1
  for(unsigned int i = 0; i<=n; i++){
    bitstring = std::vector<short>(n, 0);
    for(unsigned int j = 0; j<i; j++){
      bitstring[j] = 1;
    }
    do {
      std::vector<short> bitstringwithpartial(n);
      for(unsigned int j = 0; j<n; j++){
        if(partial[j] != -1){
          bitstringwithpartial[j] = partial[j];
        }
        else{
          bitstringwithpartial[j] = bitstring[j];
        }
      }
      if(f->check_bitstring(bitstringwithpartial)){
        assignments.push_back(bitstringwithpartial);
      }
    } while(std::prev_permutation(bitstring.begin(), bitstring.end()));
  }
}

std::ostream& operator<<(std::ostream& out, const SolvedCNF & formula){
  out << *(formula.f) << std::endl;
  out << "Assignments:" << std::endl;
  for(const auto & assig:formula.satisfying_assignments){
   int var = 1;
    for(const auto & lit : assig){
      out << "x" << var << "=" << lit << ",";
      var++;
    }
    out << std::endl;
  }
  return out;
}

bool SolvedCNF::is_frozen(int variable, std::vector<short> partial) const{
  std::vector<assignment> assignments(0);
  // bruteforce solves to check if a variable is frozen. quite ugly,
  // but since PPZ is incredibly slow anyway...
  bruteforce_solve_sat(assignments,partial);
  //if there is no satisfying assignment, the variable has the same value in all sat. assg.
  if(assignments.size() == 0){
    return true;
  }
  short value = assignments[0][variable];
  for(auto const & assig : assignments){
    if(assig[variable] != value){
      return false;
    }
  }
  return true;
}
