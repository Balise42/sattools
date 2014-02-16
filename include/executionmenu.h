#ifndef EXECUTIONMENU_H
#define EXECUTIONMENU_H 1

#include "execution.h"
#include "userinput.h"

/** Presents the user with a menu that allows them to process a formula */
class ExecutionMenu{
  private:
    /** execution context */
    Execution *ex;
    /** utility for input processing */
    UserInput *ui;
  public:
    /** default constructor*/
    ExecutionMenu(Execution * ex);
    /** destructor */
    ~ExecutionMenu();
    /** save formula to file */
    void save_formula();
    /** main loop for the menu*/
    void run();
};

#endif
