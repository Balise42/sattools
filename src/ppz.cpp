/* Basic structures: PPZ algorithm implementations (full, full with oracle, random) */
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

#include "structs.h"
#include "ppz.h"
#include "ppzrunstats.h"
#include "permstats.h"
#include "solvedcnf.h"

Ppz::Ppz(CNFFormula & formula):formula(formula),assignments(std::set<assignment>()){
}

Ppz::~Ppz(){
} 

assignment Ppz::random_solve_ppz(double limit){
  std::cout << "Starting ppz\n";
  int numtries = 0;
  std::vector<int> permutation(formula.get_n());
  std::vector<short> bitstring(formula.get_n());
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0,1);
  for(unsigned int i = 0; i<formula.get_n(); i++){
    permutation[i] = i;
  }
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  do{
    shuffle (permutation.begin(), permutation.end(), std::default_random_engine(seed));
    for(unsigned int i = 0; i<formula.get_n(); i++){
      bitstring[i] = dis(gen);
    }
    unsigned int forced = 0;
    assignment assg = execute_permutation(permutation, bitstring, forced,false);
    numtries++;
    if(assg.size() != 0 && formula.check_bitstring(assg)){
      std::cout << "Number of tries: " << numtries << std::endl;
      return assg;
    }
  } while(numtries < limit);
  std::cout << "PPZ failed.\n";
  return std::vector<short>(0);
}

void Ppz::full_solve_ppz(PpzRunStats & stats, bool oracle){
  
  unsigned int n = formula.get_n();
  std::vector<int> permutation(n, 0);
  for(unsigned int i = 0; i<n; i++){
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
        unsigned int forced = 0;
        assignment assg = execute_permutation(permutation, bitstring, forced,oracle);
        bool success = assg.size() != 0 && formula.check_bitstring(assg);
        if(success){
          assignments.insert(assg);
          stats.record_success(forced);
          PermStats * ps = dynamic_cast<PermStats *>(&stats);
          if(ps != NULL){
            ps->add_perm_to_assg(assg, permutation);
          }        
        }
        else{
          stats.record_failure(forced);
        }
      } while(std::prev_permutation(bitstring.begin(), bitstring.end()));
    }
  } while(std::next_permutation(permutation.begin(), permutation.end()));
}

assignment Ppz::execute_permutation(const std::vector<int> & permutation, const std::vector<short> & randombits, unsigned int & forced, bool oracle = false){
  forced = 0;
  unsigned n = formula.get_n();
  assignment assg(n, -1);
  CNFFormula F(formula);
  SolvedCNF solf(F);
  for(const auto & variable : permutation){
    assg[variable] = F.get_forced_value(variable);
    if(assg[variable] == -1){
      if(oracle && !solf.is_frozen(variable, assg)){
        assg[variable] = 0;
      }
      else{
        assg[variable] = randombits[variable];
      }
    }
    else{
      forced++;
    }
    F = F.make_assignment(assg);
    if(F.is_unsat()){
      return std::vector<short>(0);
    }
  }
  return assg;
}

