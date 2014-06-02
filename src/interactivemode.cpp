/* Main executable: Tiny console for formula creation and runs */
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
  while(1){
    CNFFormula f;
    FormulaCreationMenu * fcm = new FormulaCreationMenu();
    bool cont = true;
    while(1){
      try{
        cont = fcm->run(f);
        break;
      }
      catch(std::exception e){
        std::cout << e.what() << std::endl;
      }
    } 
    delete fcm;

    if(!cont){
      break;
    }
    ExecutionMenu * em = new ExecutionMenu();
    em->run(f);
    delete em;
  }
}
