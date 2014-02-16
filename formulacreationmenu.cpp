#include <iostream>
#include <vector>
#include "execution.h"
#include "formulacreationmenu.h"
#include "userinput.h"
#include "userinputexception.h"
#include "structs.h"

FormulaCreationMenu::FormulaCreationMenu(Execution * ex):ex(ex),ui(new UserInput()){
}

void FormulaCreationMenu::ask_k(){
  while(1){
    try{
      std::cout << "What is k? (maximum arity of the clauses)" << std::endl;
      std::cout << "> ";
      k = ui->getint();
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
      std::cout << "What is n? (number of variables of the formula)" << std::endl;
      std::cout << "> ";
      n = ui->getint();
      break;
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
    }
  }
}

void FormulaCreationMenu::create_file_formula(){
  ask_k();
  std::cout << "Where is your formula file?" << std::endl;
  std::cout << "> ";
  std::string filename = ui->getstring();
  try{
    ex->get_file_formula(filename, k);
  }
  catch(std::invalid_argument e){
    std::cout << e.what() << std::endl;
  }
}

void FormulaCreationMenu::create_random_formula(){
  ask_k();
  ask_n();
  int p;
  while(1){
    try{
      std::cout << "What is 1/p? (fraction of the clauses that we use - enter 5 to pick clauses with probability 1/5)" << std::endl;
      std::cout << "> ";
      p = ui->getint();
      break;
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
    }
  }
  ex->get_random_formula(n, k, p);
}

void FormulaCreationMenu::create_max_formula(){
  ask_k();
  ask_n();
  int numassg;
  while(1){
    try{
      std::cout << "How many satisfying assignments does this formula have?" << std::endl;
      std::cout << "> ";
      numassg = ui->getint();
      break;
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
    }
  }

  //now we get the assignments one by one
  std::vector<assignment> assignments(numassg);
  for(int i = 0; i<numassg; i++){
    while(1){
      try{
        std::cout << "Assignment #" << i+1 << "?" << std::endl;
        std::cout << "> ";
        assignments[i] = ui->getassignment(n);
        break;
      } 
      catch(UserInputException e){
        std::cout << e.what() << std::endl;
      }
    }
  }
  ex->get_max_formula(n, k, assignments);
}

void FormulaCreationMenu::run(){
  std::cout << "Formula creation" << std::endl;
  std::cout << "================" << std::endl << std::endl;
  std::cout << "Choose an option." << std::endl;
  std::cout << "(1) from file (DIMACS format)" << std::endl;
  std::cout << "(2) random formula" << std::endl;
  std::cout << "(3) maximum formula for a set of assignments" << std::endl << std::endl;

  std::cout << "Your choice?" << std::endl;
  std::cout << "> ";

  char choice;
  try{
    choice = ui->getchar();
  }
  catch(UserInputException e){
    std::cout << e.what() << std::endl;
    return;
  }
  switch(choice){
    case '1':
      create_file_formula();
      break;
    case '2':
      create_random_formula();
      break;
    case '3':
      create_max_formula();
      break;
    default:
      std::cout << "Please choose a valid option [1-3]" << std::endl;
  }
}
