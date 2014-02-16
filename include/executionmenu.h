#ifndef EXECUTIONMENU_H
#define EXECUTIONMENU_H 1

#include "execution.h"
#include "userinput.h"

class ExecutionMenu{
  private:
    Execution *ex;
    UserInput *ui;
  public:
    ExecutionMenu(Execution * ex);
    ~ExecutionMenu();
    void save_formula();
    void run();
};

#endif
