#ifndef FORMULACREATIONMENU_H
#define FORMULACREATIONMENU_H 1

#include "execution.h"

class FormulaCreationMenu{
  private:
    Execution * ex;
    unsigned int n, k;

  public:
    FormulaCreationMenu(Execution * ex);
    void run();
    void create_file_formula();
};

#endif
