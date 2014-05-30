/* Menu: menu used to process the created formula in the interactive mode */
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "executionmenu.h"
#include "userinput.h"
#include "userinputexception.h"
#include "ppz.h"
#include "solvedcnf.h"
#include "permstats.h"

ExecutionMenu::ExecutionMenu():ui(new UserInput()){
}

ExecutionMenu::~ExecutionMenu(){
  delete ui;
}

void ExecutionMenu::save_formula(const CNFFormula & f) const{
  std::string filename = ui->getstring("Input a filename:");
  f.save(filename);
}

void ExecutionMenu::run( CNFFormula & f) {
  while(1){
    std::cout << "Processing formula" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "(1) Solve the formula by bruteforce" << std::endl;
    std::cout << "(2) Solve the formula by full PPZ" << std::endl;
    std::cout << "(3) Solve the formula by full oracle PPZ" << std::endl;
    std::cout << "(4) Solve the formula by random PPZ" << std::endl;
    std::cout << "(5) Print formula" << std::endl;
    std::cout << "(6) Save formula" << std::endl;
    std::cout << "(7) Statistics for a given variable in a given clause" << std::endl;
    std::cout << "(0) Exit" << std::endl;

    char choice;
    try{
      choice = ui->getchar("Choose an option:");
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
      continue;
    }

    Ppz * ppz = new Ppz(f);

    switch(choice){
      case '1':
        {
          SolvedCNF * solf = new SolvedCNF(f);
          std::cout << *solf << std::endl;
          delete solf;
          break;
        }
      case '2':
        {
          PpzRunStats stats;
          ppz->full_solve_ppz(stats);
          std::cout << stats << std::endl;
          delete ppz;
          break;
        }
      case '3':
        {
          PpzRunStats stats;
          ppz->full_solve_ppz(stats,true);
          std::cout << stats << std::endl;
          delete ppz;
          break;
        }
      case '4':
        {
        double limit = pow(2, f.get_n()-1.0/f.get_k());
        ppz->random_solve_ppz(limit);
        delete ppz;
        break;
        }
      case '5':
        std::cout << f;
        break;
      case '6':
        save_formula(f);
        break;
      case '7':
        {
          std::cout << "Input your clause in DIMACS mode (including trailing 0): ";
          std::vector<int> clausespec;
          int lit;
          std::string line;
          getline(std::cin, line);
          std::stringstream ss;
          ss << line;
          while(1){
            if(ss >> lit){
              if(lit == 0){
                break;
              }
            }
            else{
              throw std::invalid_argument("Clause invalid");
            }
            clausespec.push_back(lit);
          }
          CNFClause c = CNFClause(clausespec);
          std::cout << "What variable do you want stats about? ";
          getline(std::cin,line);
          std::stringstream ss2;
          ss2 << line;
          int v = 0;
          if(!(ss2 >> v)){
            throw std::invalid_argument("Variable invalid");
          }
          PermStats stats(c, v);
          ppz->full_solve_ppz(stats,true);
          std::cout << stats << std::endl;
          delete ppz;
          break;
        }
      case '0':
        return;
        break;
      default:
        std::cout << "Please choose a valid option [0-7]" << std::endl;
        break;
    }
  }
}
