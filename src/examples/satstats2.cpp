#include <vector>
#include <algorithm>
#include <iostream>

#include "assignment.h"
#include "maxsatgenerator.h"
#include "cnfformula.h"
#include "ppz.h"
#include "ppzrunstats.h"
#include "solvedcnf.h"

int main(){
  std::vector<std::vector<short> > bitstrings;
  std::vector<short> bitstring;
  //we enumerate all the bitstrings 
  //that have 2 bits to 1
  bitstring = std::vector<short>(8, 0);
  bitstring[0] = 1;
  bitstring[1] = 1;
  do{
    bitstrings.push_back(bitstring);
  } while(std::prev_permutation(bitstring.begin(), bitstring.end()));

  std::vector<short> pick16(bitstrings.size(), 0);
  for(int i = 0; i<16; i++){
    pick16[i] = 1;
  }

  do{
    std::vector<Assignment> assignments;
    for(int i = 0; i<pick16.size(); i++){
      if(pick16[i] == 1){
        assignments.push_back(Assignment(bitstrings[i]));
      }
    }
    MaxSatGenerator g(8, 3, assignments);
    CNFFormula f;
    g.generate_sat(f);
    SolvedCNF solf(f);
    if(solf.get_satisfying_assignments().size() <=18){
      std::cout << solf;
    }
  } while(std::prev_permutation(pick16.begin(), pick16.end()));
}
