#ifndef EXECUTIONMENU_H
#define EXECUTIONMENU_H 1

#include "cnfformula.h"
#include "userinput.h"

/** Presents the user with a menu that allows them to process a formula */
class ExecutionMenu{
  private:
    /** utility for input processing */
    UserInput *ui;
    /** save formula to file */
    void save_formula(const CNFFormula & f) const;
  public:
    /** default constructor*/
    ExecutionMenu();
    /** destructor */
    ~ExecutionMenu();
    /** main loop for the menu*/
    void run(CNFFormula & f);
};

#endif
