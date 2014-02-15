#include <iostream>
#include "execution.h"
#include "formulacreationmenu.h"

FormulaCreationMenu::FormulaCreationMenu(Execution * ex):ex(ex){
}



void FormulaCreationMenu::create_file_formula(){
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
  std::cin >> choice;
  switch(choice){
    case '1':
      create_file_formula();
      break;
    case '2':
      break;
    case '3':
      break;
    default:
      std::cout << "Please choose a valid option [1-3]" << std::endl;
  }
}
