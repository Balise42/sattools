#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <vector>
#include <string>
#include <exception>
#include "commandline.h"
#include "cnfformula.h"
#include "dimacsgenerator.h"
#include "ppz.h"
#include "randomsatgenerator.h"
#include "maxsatgenerator.h"
#include "interactivemode.h"
#include "cliexception.h"

CommandLine::CommandLine(int argc, char ** argv):formula_init(false),desc(new po::options_description("Options")),vm(new po::variables_map()){
  desc->add_options()
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
  po::store(po::parse_command_line(argc, argv, *desc), *vm);
  po::notify(*vm);
}

CommandLine::~CommandLine(){
  delete ppz;
  delete vm;
  delete desc;
  delete f;
}

void CommandLine::print_help(){
  std::cout << *desc << std::endl;
}

void CommandLine::get_file_formula(std::string filename, unsigned int k){
  std::ifstream file(filename);
  if(file.is_open()){
    DimacsGenerator dg(file, k);
    f = new CNFFormula(dg.generate_sat());
  }
  else{
    throw std::invalid_argument("File does not exist");
  }
}

void CommandLine::parse_file_options(){
  if(!vm->count("k")){
    std::cerr << "Need to provide k when providing a file" << std::endl;
    throw CLIException("k was not provided where needed");
  }
  std::string filename = (*vm)["file"].as<std::string>();
  k = (*vm)["k"].as<unsigned int>();
  get_file_formula(filename, k);
  //if throws, formula_init is not set to true
  formula_init = true;
}

void CommandLine::get_random_formula(unsigned int n, unsigned int k, unsigned int p){
  RandomSatGenerator rg(n, k, p);
  f = new CNFFormula(rg.generate_formula());
}

void CommandLine::parse_random(){
  if(!vm->count("n") || !vm->count("k")){
    std::cerr << "Need to provide n and k for random generator" << std::endl;
    throw CLIException("n or k was not provided where needed");
  }
  n = (*vm)["n"].as<unsigned int>();
  k = (*vm)["k"].as<unsigned int>();
  unsigned int p = (*vm)["random"].as<unsigned int>();
  get_random_formula(n, k, p);
  //if throws, formula_init is not set to true
  formula_init = true;
}

void CommandLine::parse_max(){
  if(!vm->count("n") || !vm->count("k")){
    std::cerr << "Need to provide n and k for random generator" << std::endl;
    throw CLIException("n or k was not provided where needed");
  }
  if(!vm->count("assignment")){
    std::cerr << "Need to provide assignments for max formulas" << std::endl;
    throw CLIException("No assignment provided for max formula");
  }
  n = (*vm)["n"].as<unsigned int>();
  k = (*vm)["k"].as<unsigned int>();
  std::vector<std::string> strass = (*vm)["assignment"].as<std::vector<std::string> >();
  std::vector<assignment> assignments;
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
        throw std::invalid_argument("Invalid assignment");
      }
    }
    assignments.push_back(a);
  }
  get_max_formula(n, k, assignments);
  formula_init = true;
}

void CommandLine::get_max_formula(unsigned int n, unsigned int k, std::vector<assignment> & as){
  MaxSatGenerator mg(n, k, as);
  f = new CNFFormula(mg.generate_sat());
}

void CommandLine::bruteforce(){
  CNFFormula * f2 = new CNFFormula(*f);
  f2->bruteforce_solve_sat();
  std::cout << *f2;
  delete f2;
}

void CommandLine::ppzfull(){
  if(!ppz){
    ppz = new Ppz(f);
  }
  ppz->full_solve_ppz();
  std::cout << *ppz << std::endl;
}

void CommandLine::ppzrandom(){
  CNFFormula * f2 = new CNFFormula(*f);
  Ppz ppzr(f2);
  double limit = pow(2, n-1.0/k);
  ppzr.random_solve_ppz(limit);
}

void CommandLine::ppzfulloracle(){
  if(!ppz){
    ppz = new Ppz(f);
  }
  ppz->full_solve_ppz(true);
  std::cout << *ppz << std::endl;
}

void CommandLine::parse_and_exec(){
  try{
  if(vm->count("help")){
    print_help();
    return;
  }
  else if(vm->count("interactive")){
    InteractiveMode * im = new InteractiveMode();
    im->start();
    return;
  }
  else{
    if(vm->count("file") + vm->count("max") + vm->count("random") != 1){
      std::cerr << "Need to provide exactly one of 'file', 'max' or 'random' options when not using interactive mode." << std::endl;
      return;
    }
    if(vm->count("file")){
      parse_file_options();
    }
    if(vm->count("random")){
      parse_random();
    }
    if(vm->count("max")){
      parse_max();
    }
  }
  if(!formula_init){
    //if by now we don't have a formula (but didn't throw before) something wrong happened
    throw std::runtime_error("Formula has not been initialized");
  }

  if(vm->count("bruteforce")){
    bruteforce();
  }

  if(vm->count("ppzfull")){
    ppzfull();
  }

  if(vm->count("ppzfulloracle")){
    ppzfulloracle();
  }

  if(vm->count("ppzrandom")){
    ppzrandom();
  }

  if(vm->count("save")){
    savefilename = (*vm)["save"].as<std::string>();
  }

  f->save(savefilename);
  }
  catch(std::exception & e){
    std::cerr << e.what() << std::endl;
  }
}
