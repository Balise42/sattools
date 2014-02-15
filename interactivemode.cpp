#include "interactivemode.h"
#include "execution.h"
#include "formulacreationmenu.h"

InteractiveMode::InteractiveMode():ex(new Execution()){
}

InteractiveMode::~InteractiveMode(){
  delete ex;
}

void InteractiveMode::start(){
  while(!ex->is_formula_init()){
    FormulaCreationMenu * fcm = new FormulaCreationMenu(ex);
    fcm->run();
  }
}
