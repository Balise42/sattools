#include <vector>
#include <algorithm>
#include <iostream>

#include "assignment.h"
#include "maxsatgenerator.h"
#include "cnfformula.h"
#include "ppz.h"
#include "ppzrunstats.h"

int main(){
  std::vector<std::vector<short> > bitstrings;
  std::vector<short> bitstring;
  //we enumerate all the bitstrings by taking all permutations 
  //of strings that have i bits to 1
  for(unsigned int i = 0; i<=5; i++){
    bitstring = std::vector<short>(5, 0);
    for(unsigned int j = 0; j<i; j++){
      bitstring[j] = 1;
    }
    do{
      bitstrings.push_back(bitstring);
    } while(std::prev_permutation(bitstring.begin(), bitstring.end()));
  }
  std::vector<short> pick3(bitstrings.size(), 0);
  pick3[0] = 1;
  pick3[1] = 1;
  pick3[2] = 1;

  do{
    std::vector<Assignment> assignments;
    for(int i = 0; i<pick3.size(); i++){
      if(pick3[i] == 1){
        assignments.push_back(Assignment(bitstrings[i]));
      }
    }
    for(int i = 0; i<1; i++){
      MaxSatGenerator g(5, 3, assignments);
      CNFFormula f;
      g.generate_sat(f);
      f.minimalize();
      PpzRunStats stats1;
      PpzRunStats stats2;
      Ppz ppz(f);
      ppz.full_solve_ppz(stats1);
      Ppz ppzo(f);
      ppz.full_solve_ppz(stats2, true);
      std::cout << stats1.satisfying_cases << " " << stats2.satisfying_cases << std::endl; 
    }
  } while(std::prev_permutation(pick3.begin(), pick3.end()));
}
