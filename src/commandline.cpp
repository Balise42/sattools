/* Main executable: command line parsing and dispatching */
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <vector>
#include <string>
#include "commandline.h"
#include "cnfformula.h"
#include "interactivemode.h"
#include "cliexception.h"
#include "structs.h"
#include "dimacsgenerator.h"
#include "maxsatgenerator.h"
#include "randomsatgenerator.h"
#include "solvedcnf.h"

CommandLine::CommandLine(int argc, char ** argv):desc(new po::options_description("Options")),vm(new po::variables_map()){
  desc->add_options()
    ("help,h", "Print help message")
    ("n,n", po::value<unsigned int>(), "Number of variables")
    ("k,k", po::value<unsigned int>(), "Arity of a clause")
    ("file,f", po::value<std::string>(), "Get formula from file")
    ("random,r", po::value<unsigned int>(), "Get random formula with given frequency of clause (e.g. enter 5 to pick 1 out of 5 clauses on average)")
    ("max,m", "Get maximum formula from a set of assignments")
    ("assignment,a", po::value<std::vector<std::string> >(), "List of assignments for -m")
    ("interactive,i", "Interactive mode")
    ("minimalize", "Minimalize the formula before doing anything else")
    ("bruteforce", "Solve by bruteforce - warning, all case exponential time algorithm!")
    ("ppzfull", "Solve by full ppz - warning, all case superexponential time algorithm!")
    ("ppzfulloracle", "Solve by full ppz with oracle - warning, all case superexponential time algorithm!")
    ("ppzrandom", "Solve by random ppz - warning, worst case exponential time algorithm!")
    ("save,s", po::value<std::string>()->default_value("formula.cnf"),"Save the formula in DIMACS format in given file. Default is save in 'formula.cnf'.");
  po::store(po::parse_command_line(argc, argv, *desc), *vm);
  po::notify(*vm);
}

CommandLine::~CommandLine(){
  delete vm;
  delete desc;
}

void CommandLine::print_help(){
  std::cout << *desc << std::endl;
}

void CommandLine::parse_file_options(CNFFormula & f){
  if(!vm->count("k")){
    std::cerr << "Need to provide k when providing a file" << std::endl;
    throw CLIException("k was not provided where needed");
  }
  std::string filename = (*vm)["file"].as<std::string>();
  unsigned int k = (*vm)["k"].as<unsigned int>();
  DimacsGenerator dg(filename, k);
  dg.generate_sat(f);
}

void CommandLine::parse_random(CNFFormula & f){
  if(!vm->count("n") || !vm->count("k")){
    std::cerr << "Need to provide n and k for random generator" << std::endl;
    throw CLIException("n or k was not provided where needed");
  }
  unsigned int n = (*vm)["n"].as<unsigned int>();
  unsigned int k = (*vm)["k"].as<unsigned int>();
  unsigned int p = (*vm)["random"].as<unsigned int>();
  RandomSatGenerator rg(n, k, p);
  rg.generate_formula(f);
}

void CommandLine::parse_max(CNFFormula & f){
  if(!vm->count("n") || !vm->count("k")){
    std::cerr << "Need to provide n and k for random generator" << std::endl;
    throw CLIException("n or k was not provided where needed");
  }
  if(!vm->count("assignment")){
    std::cerr << "Need to provide assignments for max formulas" << std::endl;
    throw CLIException("No assignment provided for max formula");
  }
  unsigned int n = (*vm)["n"].as<unsigned int>();
  unsigned int k = (*vm)["k"].as<unsigned int>();
  std::vector<std::string> strass = (*vm)["assignment"].as<std::vector<std::string> >();
  std::vector<Assignment> assignments;
  for(const auto & as : strass){
    Assignment a;
    a.set_assignment(as);
    assignments.push_back(a);
  }
  MaxSatGenerator mg(n, k, assignments);
  mg.generate_sat(f);
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
    if(vm->count("file") + vm->count("max") + vm->count("random") != 1){
      std::cerr << "Need to provide exactly one of 'file', 'max' or 'random' options when not using interactive mode." << std::endl;
      return;
    }

    CNFFormula f;

    if(vm->count("file")){
      parse_file_options(f);
    }
    if(vm->count("random")){
      parse_random(f);
    }
    if(vm->count("max")){
      parse_max(f);
    }

    if(vm->count("minimalize")){
      f.minimalize();
    }
  
    if(vm->count("bruteforce")){
      SolvedCNF * solf = new SolvedCNF(f);
      std::cout << *solf << std::endl;
      delete solf;
    }

    if(vm->count("ppzfull")){
      Ppz * ppz = new Ppz(f);
      PpzRunStats stats;
      ppz->full_solve_ppz(stats);
      std::cout << stats << std::endl;
      delete ppz;
    }

    if(vm->count("ppzfulloracle")){
      Ppz * ppz = new Ppz(f);
      PpzRunStats stats;
      ppz->full_solve_ppz(stats,true);
      std::cout << stats << std::endl;
      delete ppz;
    }

    if(vm->count("ppzrandom")){
      Ppz * ppz = new Ppz(f);
      double limit = pow(2, f.get_n()-1.0/f.get_k());
      ppz->random_solve_ppz(limit);
    }

    std::string savefilename = "formula.cnf";
    if(vm->count("save")){
      savefilename = (*vm)["save"].as<std::string>();
      f.save(savefilename);
    }
  }

  catch(std::exception & e){
    std::cerr << e.what() << std::endl;
  }
}
