#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include <vector>
#include "cnfformula.h"
#include "dimacsgenerator.h"
#include "ppz.h"
#include "randomsatgenerator.h"
#include "maxsatgenerator.h"

CNFFormula get_file_formula(std::string filename, int k){
  std::ifstream file(filename);
  if(file.is_open()){
    DimacsGenerator dg(file, k);
    return dg.generate_sat();
  }
  throw;
}

CNFFormula get_max_formula(unsigned int n, unsigned int k, std::vector<assignment> as){
  MaxSatGenerator mg(n,k,as);
  return mg.generate_sat();
}

CNFFormula get_random_formula(unsigned int n, unsigned int k, unsigned int p){
  RandomSatGenerator rg(n,k,p);
  return rg.generate_formula();
}

int main(int argc, char** argv){
  CNFFormula f;
  bool formula_init = false;
  unsigned int n, k;
  std::string savefilename = "formula.cnf";
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help,h", "Print help message")
    ("n,n", po::value<unsigned int>(), "Number of variables")
    ("k,k", po::value<unsigned int>(), "Arity of a clause")
    ("file,f", po::value<std::string>(), "Get formula from file")
    ("random,r", po::value<unsigned int>(), "Get random formula with given random range")
    ("max,m", "Get maximum formula from a set of assignments")
    ("assignment,a", po::value<std::vector<std::string> >(), "List of assignments for -m")
    ("interactive,i", "Interactive mode")
    ("bruteforce", "Solve by bruteforce - warning, all case exponential time algorithm!")
    ("ppzfull", "Solve by full ppz - warning, all case superexponential time algorithm!")
    ("ppzfulloracle", "Solve by full ppz with oracle - warning, all case superexponential time algorithm!")
    ("ppzrandom", "Solve by random ppz - warning, worst case exponential time algorithm!")
    ("save,s", po::value<std::string>(),"Save the formula in DIMACS format in given file. Default is save in 'formula.cnf'.");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);

  if(vm.count("help")){
    std::cout << desc << std::endl;
  }
  else if(vm.count("interactive")){
    std::cout << "Interactive mode not implemented yet." << std::endl;
    return -1;
  }
  else{
    if(vm.count("file")){
      if(!vm.count("k")){
        std::cerr << "Need to provide k when providing a file" << std::endl;
        return -1;
      }
      std::string filename = vm["file"].as<std::string>();
      k = vm["k"].as<unsigned int>();
      f = get_file_formula(filename, k);
      formula_init = true;
    }
    else if(!vm.count("n") || !vm.count("k")){
      std::cerr << "Need to provide n and k if not providing a file" << std::endl;
      return -1;
    }
    k = vm["k"].as<unsigned int>();
    if(vm.count("random")){
      n = vm["n"].as<unsigned int>();
      unsigned int p = vm["random"].as<unsigned int>();
      f = get_random_formula(n, k, p);
      formula_init = true;
    }
    else if(vm.count("max")){
      n = vm["n"].as<unsigned int>();
      if(!vm.count("assignment")){
        std::cerr << "Need to provide assignments for max formulas (or -a none for empty formula)" << std::endl;
      }
      std::vector<assignment> assignments;
      std::vector<std::string> strass = vm["assignment"].as<std::vector<std::string> >();
      for(const auto & as : strass){
        assignment a;
        for(const auto & ch : as){
          if(ch == '0'){
            a.push_back(0);
          }
          else if(ch == '1'){
            a.push_back(1);
          }
          else{
            std::cerr << "Invalid assignment " << ch << std::endl;
            return -1;
          }
        }
        assignments.push_back(a);
      }
      f = get_max_formula(n, k, assignments);
      formula_init = true;
    }
  }
  if(!formula_init){
    std::cerr << "Need to provide a formula." << std::endl;
    return -1;
  }
  if(vm.count("bruteforce")){
    CNFFormula f2 = f;
    f2.bruteforce_solve_sat();
    std::cout << f2;
  }
  if(vm.count("ppzfull") || vm.count("ppzfulloracle")){
    CNFFormula f2 = f;
    Ppz ppz(&f);

    if(vm.count("ppzfull")){
      ppz.full_solve_ppz();
    }
    if(vm.count("ppzfulloracle")){
      ppz.full_solve_ppz(true);  
    }
    std::cout << ppz << std::endl;
  }
  if(vm.count("ppzrandom")){
    CNFFormula f2 = f;
    Ppz ppz(&f);
    double limit = pow(2, n-1.0/k);
    ppz.random_solve_ppz(limit);
  }
  if(vm.count("save")){
    savefilename = vm["save"].as<std::string>();
  }
  f.save(savefilename);
}
