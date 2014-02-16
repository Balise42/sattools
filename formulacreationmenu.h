#ifndef FORMULACREATIONMENU_H
#define FORMULACREATIONMENU_H 1

#include "execution.h"
#include "userinput.h"

class FormulaCreationMenu{
  private:
    Execution * ex;
    unsigned int n, k;
    UserInput * ui;

  public:
    FormulaCreationMenu(Execution * ex);
    void run();
    void ask_k();
    void ask_n();
    void create_file_formula();
    void create_random_formula();
    void create_max_formula();

};

#endif
