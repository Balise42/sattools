#include "interactivemode.h"
#include "formulacreationmenu.h"
#include "executionmenu.h"
#include "cnfformula.h"
#include <exception>

InteractiveMode::InteractiveMode(){
}

InteractiveMode::~InteractiveMode(){
}

void InteractiveMode::start(){
  CNFFormula f;
  FormulaCreationMenu * fcm = new FormulaCreationMenu();
  while(1){
    try{
      fcm->run(f);
      break;
    }
    catch(std::exception e){
      std::cout << e.what() << std::endl;
    }
  } 
  delete fcm;

  ExecutionMenu * em = new ExecutionMenu();
  em->run(f);
  delete em;
}
