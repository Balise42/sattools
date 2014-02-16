#include <iostream>
#include <string>
#include <cmath>
#include "executionmenu.h"
#include "userinput.h"
#include "userinputexception.h"
#include "ppz.h"
#include "solvedcnf.h"

ExecutionMenu::ExecutionMenu():ui(new UserInput()){
}

ExecutionMenu::~ExecutionMenu(){
  delete ui;
}

void ExecutionMenu::save_formula(const CNFFormula & f) const{
  std::cout << "Input a filename: " << std::endl;
  std::cout << "> ";
  std::string filename = ui->getstring();
  f.save(filename);
}

void ExecutionMenu::run( CNFFormula & f) {
  while(1){
    std::cout << "Processing formula" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "Choose an option." << std::endl;
    std::cout << "(1) Solve the formula by bruteforce" << std::endl;
    std::cout << "(2) Solve the formula by full PPZ" << std::endl;
    std::cout << "(3) Solve the formula by full oracle PPZ" << std::endl;
    std::cout << "(4) Solve the formula by random PPZ" << std::endl;
    std::cout << "(5) Print formula" << std::endl;
    std::cout << "(6) Save formula" << std::endl; 
    std::cout << "(7) Exit" << std::endl;

    char choice;
    try{
      choice = ui->getchar();
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
      continue;
    }

    Ppz * ppz = new Ppz(&f);

    switch(choice){
      case '1':
        {
        SolvedCNF * solf = new SolvedCNF(f);
        std::cout << *solf << std::endl;
        delete solf;
        break;
        }
      case '2':
        ppz->full_solve_ppz();
        std::cout << *ppz << std::endl;
        delete ppz;
        break;
      case '3':
        ppz->full_solve_ppz(true);
        std::cout << *ppz << std::endl;
        delete ppz;
        break;
      case '4':
        {
        ppz->full_solve_ppz(true);
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
        return;
        break;
      default:
        std::cout << "Please choose a valid option [0-7]" << std::endl;
        break;
    }
  }
}
