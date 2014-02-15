#include <fstream>
#include <stdexcept>
#include <cmath>
#include "dimacsgenerator.h"
#include "cnfformula.h"
#include "execution.h"
#include "randomsatgenerator.h"
#include "maxsatgenerator.h"

Execution::Execution():formula_init(false){
}

Execution::~Execution(){
  delete f;
  delete originalf;
  delete ppz;
}

void Execution::get_file_formula(std::string filename, unsigned int k){
  std::ifstream file(filename);
  if(file.is_open()){
    DimacsGenerator dg(file, k);
    f = new CNFFormula(dg.generate_sat());
    originalf = new CNFFormula(*f);
    formula_init = true;
  }
  else{
    throw std::invalid_argument("File does not exist");
  }
}

void Execution::get_random_formula(unsigned int n, unsigned int k, unsigned int p){
  RandomSatGenerator rg(n, k, p);
  f = new CNFFormula(rg.generate_formula());
  originalf = new CNFFormula(*f);
  formula_init = true;
}

void Execution::get_max_formula(unsigned int n, unsigned int k, std::vector<assignment> & as){
  MaxSatGenerator mg(n, k, as);
  f = new CNFFormula(mg.generate_sat());
  originalf = new CNFFormula(*f);
  formula_init = true;
}

void Execution::bruteforce(){
  if(!formula_init){
    throw std::runtime_error("Formula is not initialized");
  }
  f->bruteforce_solve_sat();
  std::cout << *f;
}

void Execution::ppzfull(){
  if(!formula_init){
    throw std::runtime_error("Formula is not initialized");
  }
  if(!ppz){
    ppz = new Ppz(f);
  }
  ppz->full_solve_ppz();
  std::cout << *ppz << std::endl;
}

void Execution::ppzrandom(){
  if(!formula_init){
    throw std::runtime_error("Formula is not initialized");
  }
  if(!ppz){
    ppz = new Ppz(f);
  }
  double limit = pow(2, n-1.0/k);
  ppz->random_solve_ppz(limit);
}

void Execution::ppzfulloracle(){
  if(!formula_init){
    throw std::runtime_error("Formula is not initialized");
  }
  if(!ppz){
    ppz = new Ppz(f);
  }
  ppz->full_solve_ppz(true);
  std::cout << *ppz << std::endl;
}

void Execution::save(std::string filename){
  f->save(filename);
}
