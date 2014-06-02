/* Menu: menu used by the interactive mode to create a formula */
#include <iostream>
#include <vector>
#include "cnfformula.h"
#include "formulacreationmenu.h"
#include "userinput.h"
#include "userinputexception.h"
#include "structs.h"
#include "dimacsgenerator.h"
#include "maxsatgenerator.h"
#include "randomsatgenerator.h"
#include "solvedcnf.h"
#include "assignment.h"


FormulaCreationMenu::FormulaCreationMenu():ui(new UserInput()){
}

FormulaCreationMenu::~FormulaCreationMenu(){
  delete ui;
}

void FormulaCreationMenu::ask_k(){
  while(1){
    try{
      k = ui->getint("What is k? (maximum arity of the clauses)");
      break;
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
    }
  }
}

void FormulaCreationMenu::ask_n(){
  while(1){
    try{
      n = ui->getint("What is n? (number of variables of the formula)");
      break;
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
    }
  }
}

void FormulaCreationMenu::create_file_formula(CNFFormula & f) {
  ask_k();
  std::string filename = ui->getstring("Where is your formula file?");
  DimacsGenerator dg(filename, k);
  dg.generate_sat(f); 
}

void FormulaCreationMenu::create_random_formula(CNFFormula & f) {
  ask_k();
  ask_n();
  int p;
  while(1){
    try{
      p = ui->getint("What is 1/p? (fraction of the clauses that we use - enter 5 to pick clauses with probability 1/5)");
      break;
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
    }
  }
  RandomSatGenerator rg(n, k, p);
  rg.generate_formula(f);
}

void FormulaCreationMenu::create_max_formula(CNFFormula & f) {
  ask_k();
  ask_n();
  int numassg;
  while(1){
    try{
      numassg = ui->getint("How many satisfying assignments does this formula have?");
      break;
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
    }
  }

  //now we get the assignments one by one
  std::vector<Assignment> assignments(numassg);
  for(int i = 0; i<numassg; i++){
    while(1){
      try{
        assignments[i] = ui->getassignment(n,std::string("Assignment #").append(std::to_string(i+1)).append("?"));
        break;
      } 
      catch(UserInputException e){
        std::cout << e.what() << std::endl;
      }
    }
  }
  MaxSatGenerator mg(n, k, assignments);
  mg.generate_sat(f);
}

bool FormulaCreationMenu::run(CNFFormula & f){
  std::cout << "Formula creation" << std::endl;
  std::cout << "================" << std::endl << std::endl;
  std::cout << "Choose an option." << std::endl;
  std::cout << "(1) from file (DIMACS format)" << std::endl;
  std::cout << "(2) random formula" << std::endl;
  std::cout << "(3) maximum formula for a set of assignments" << std::endl << std::endl;


  char choice;
  choice = ui->getchar("Your choice?");
 
  switch(choice){
    case '1':
      create_file_formula(f);
      return true;
      break;
    case '2':
      create_random_formula(f);
      return true;
      break;
    case '3':
      create_max_formula(f);
      return true;
      break;
    default:
      std::cout << "Please choose a valid option [1-3]" << std::endl;
      return false;
      break;
  }
}
