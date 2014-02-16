#include <iostream>
#include <string>
#include "execution.h"
#include "executionmenu.h"
#include "userinput.h"
#include "userinputexception.h"

ExecutionMenu::ExecutionMenu(Execution * ex):ex(ex),ui(new UserInput()){
}

ExecutionMenu::~ExecutionMenu(){
  delete ui;
}

void ExecutionMenu::save_formula(){
  std::cout << "Input a filename: " << std::endl;
  std::cout << "> ";
  std::string filename = ui->getstring();
  ex->save(filename);
}

void ExecutionMenu::run(){
  while(1){
    std::cout << "Processing formula" << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "Choose an option." << std::endl;
    std::cout << "(1) Solve the formula by bruteforce" << std::endl;
    std::cout << "(2) Solve the formula by full PPZ" << std::endl;
    std::cout << "(3) Solve the formula by full oracle PPZ" << std::endl;
    std::cout << "(4) Solve the formula by random PPZ" << std::endl;
    std::cout << "(5) Clear all PPZ executions" << std::endl;
    std::cout << "(6) Restart execution with a clean identical formula" << std::endl;
    std::cout << "(7) Save formula" << std::endl;
    std::cout << "(8) Print formula info" << std::endl;
    std::cout << "(9) Print PPZ info" << std::endl;
    std::cout << "(0) Exit" << std::endl;

    char choice;
    try{
      choice = ui->getchar();
    }
    catch(UserInputException e){
      std::cout << e.what() << std::endl;
      continue;
    }

    switch(choice){
      case '1':
        ex->bruteforce();
        break;
      case '2':
        ex->ppzfull();
        break;
      case '3':
        ex->ppzfulloracle();
        break;
      case '4':
        ex->ppzrandom();
        break;
      case '5':
        ex->clearppz();
        break;
      case '6':
        ex->restart();
        break;
      case '7':
        save_formula();
        break;
      case '8':
        ex->print_formula();
        break;
      case '9':
        ex->print_ppz();
        break;
      case '0':
        return;
      default:
        std::cout << "Please choose a valid option [0-9]" << std::endl;
        break;
    }
  }
}
