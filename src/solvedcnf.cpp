/* Basic structures: a solved CNF formula (by bruteforce) - also allows checking for frozen variables. */
#include <algorithm>
#include <vector>
#include <iostream>
#include "solvedcnf.h"
#include "cnfformula.h"
#include "assignment.h"

SolvedCNF::SolvedCNF(const CNFFormula & f):f(new CNFFormula(f)),satisfying_assignments(std::vector<Assignment>(0)){
  bruteforce_solve_sat(satisfying_assignments);
}

SolvedCNF::~SolvedCNF(){
  delete f;
}

void SolvedCNF::bruteforce_solve_sat(std::vector<Assignment> & assignments, Assignment partial) const {
  unsigned int n = f->get_n();
  if(partial.size() == 0){
    partial = Assignment(n);
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
      Assignment bitstringwithpartial(n);
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

bool SolvedCNF::is_frozen(int variable, Assignment partial) const{
  std::vector<Assignment> assignments(0);
  for(auto const & assig : satisfying_assignments){
    if(assig.is_compatible(partial)){
      assignments.push_back(assig);
    }
  }
  //if there is zero or one satisfying assignment, the variable has the same value in all sat. assg.
  if(assignments.size() <= 1){
    return true;
  }
  //otherwise we check whether the variable has the same value in all compatible assignments
  short value = assignments[0][variable];
  for(auto const & assig : assignments){
    if(assig[variable] != value){
      return false;
    }
  }
  return true;
}
