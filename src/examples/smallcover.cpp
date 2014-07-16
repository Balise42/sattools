#include <iostream>
#include <vector>
#include <algorithm>
#include "cnfclause.h"
#include "solvedcnf.h"
#include "cnfformula.h"
#include "assignment.h"
#include "structs.h"

const unsigned int NUMVARS = 4;

int main(){
  std::vector<SolvedCNF> chains;
  std::vector<unsigned int> chaindef(NUMVARS);
  for(unsigned int i = 0; i<NUMVARS; i++){
    chaindef[i] = i;
  }
  do {
    std::vector<unsigned int> pattern(NUMVARS, 0);
    for(unsigned int i = 0; i<=NUMVARS; i++){
      for(unsigned int j = 0; j<i; j++){
        pattern[j] = 1;
      }
      do{
        CNFFormula f(NUMVARS,2);
        std::vector<literal> lits(NUMVARS);
        for(unsigned int j = 0; j<NUMVARS; j++){
          literal l;
          l.variable = chaindef[j];
          l.value = pattern[j];
          lits[j] = l;
        }
        for(unsigned int j = 0; j<NUMVARS; j++){
          CNFClause c;
          c.add_literal(lits[j]);
          c.add_literal(lits[(j+1)%NUMVARS]);
          f.add_clause(c);
        }
        SolvedCNF solf(f);
        chains.push_back(solf);
      } while(std::prev_permutation(pattern.begin(), pattern.end()));
    }
  } while(std::next_permutation(chaindef.begin(), chaindef.end()));

  std::vector<Assignment> all_assig;
  for(unsigned int i = 0; i<=NUMVARS; i++){
    std::vector<short> assigvec(NUMVARS, 0);
    for(unsigned int j = 0; j<i; j++){
      assigvec[j] = 1;
    }
    do{
      all_assig.push_back(assigvec);
    } while(std::prev_permutation(assigvec.begin(), assigvec.end()));
  }

  for(unsigned int i = 0; i<=all_assig.size(); i++){
    std::cout << "i = " << i << std::endl;
    std::vector<short> covercandidatechoice(all_assig.size(), 0);
    for(unsigned int j = 0; j<i; j++){
      covercandidatechoice[j] = 1;
    }
    do{
      std::vector<Assignment> covercandidate;
      for(unsigned int j = 0; j<all_assig.size(); j++){
        if(covercandidatechoice[j] == 1){
          covercandidate.push_back(all_assig[j]);
        }
      }
      bool validcover = true;
      for(auto chain : chains){
        std::vector<Assignment> chainsat = chain.get_satisfying_assignments();
        bool covered = false;
        for(auto assig : covercandidate){

          if(std::find(chainsat.begin(), chainsat.end(), assig) != chainsat.end()){
            covered = true;
            break;
          }
        }
        if(covered == false){
          validcover = false;
          break;
        }
      }
      if(validcover){
        for(auto assig : covercandidate){
          std::cout << assig;
        }
        std::cout << std::endl;
      }
    } while(std::prev_permutation(covercandidatechoice.begin(), covercandidatechoice.end()));
  }
}
