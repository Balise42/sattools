/* Basic structures: PPZ algorithm implementations (full, full with oracle, random) */
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>
#include <boost/thread.hpp>

#include "structs.h"
#include "ppz.h"
#include "ppzrunstats.h"
#include "permstats.h"
#include "solvedcnf.h"
#include "assignment.h"

Ppz::Ppz(CNFFormula & formula):formula(formula),assignments(std::set<Assignment>()){
}

Ppz::~Ppz(){
} 

Assignment Ppz::random_solve_ppz(double limit){
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
    bool nf = false;
    bool trackedvar = -1;
    Assignment assg = execute_bitstring(permutation, bitstring, forced,nf, trackedvar, false);
    numtries++;
    if(assg.size() != 0 && formula.check_bitstring(assg)){
      std::cout << "Number of tries: " << numtries << std::endl;
      return assg;
    }
  } while(numtries < limit);
  std::cout << "PPZ failed.\n";
  return Assignment(0);
}

void Ppz::full_solve_ppz(PpzRunStats & stats, bool oracle){
 
  unsigned int n = formula.get_n();
  std::vector<int> permutation(n, 0);
  for(unsigned int i = 0; i<n; i++){
    permutation[i] = i;
  }

  bool cont = true;
  while(1){
    boost::thread thr[PPZ_NB_THREADS];
    for(int i = 0; i<PPZ_NB_THREADS; i++){
      thr[i] = boost::thread(&Ppz::execute_permutation, this, permutation, oracle, &stats);
      if(!std::next_permutation(permutation.begin(), permutation.end())){
        cont = false;
        break;
      }
    }
    for(int i = 0; i<PPZ_NB_THREADS; i++){
      thr[i].join();
    }
    if(!cont){
      break;
    }
  }
  
}

void Ppz::execute_permutation(const std::vector<int> & permutation, bool oracle, PpzRunStats * stats){
  unsigned int n = formula.get_n();
    //we enumerate all the bitstrings by taking all permutations of strings
    //that have i bits to 1
  std::vector<short> bitstring;
  PermStats * ps = dynamic_cast<PermStats *>(stats);
  Assignment forperm;
  bool nf = false;
  for(unsigned int i = 0; i<= n; i++){
    Assignment assg;
    bitstring = std::vector<short>(n, 0);
    for(unsigned int j = 0; j<i; j++){
      bitstring[j] = 1;
    }


    int trackedvar = -1;
    do {
      assg.clear();
      std::set<Assignment> tmpassg;
      unsigned int forced = 0;
      if(ps != NULL){
        trackedvar = ps->get_variable();
      }
      bool nftmp = false;
      assg = execute_bitstring(permutation, bitstring, forced,nftmp, trackedvar, oracle);
      
      bool success = assg.size() != 0 && formula.check_bitstring(assg);
      if(success){
        forperm = assg;
        nf = nf || nftmp;
        stats->record_success(forced);
        tmpassg.insert(assg); 
        if(ps != NULL){
          ps->add_perm_to_assg(assg, permutation);
        }
      }
      else{
        stats->record_failure(forced);
      }
      {
        boost::lock_guard<boost::mutex> guard(assgmutex);
        assignments.insert(tmpassg.begin(), tmpassg.end());
      }
    } while(std::prev_permutation(bitstring.begin(), bitstring.end()));
  }
  if(ps != NULL){
    ps->set_nf_to_perm(forperm, nf);
  }
}

Assignment Ppz::execute_bitstring(const std::vector<int> & permutation, const std::vector<short> & randombits, unsigned int & forced, bool & nf, int trackedvar = -1, bool oracle = false){
  forced = 0;
  unsigned n = formula.get_n();
  Assignment assg(n);
  CNFFormula F(formula);
  SolvedCNF solf(F);
  for(const auto & variable : permutation){
    assg[variable] = F.get_forced_value(variable);
    if(assg[variable] == -1){
      if(oracle && !solf.is_frozen(variable, assg)){
        if(trackedvar-1 == variable){
          nf = true;
        }
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
      return Assignment(0);
    }
  }
  return assg;
}

