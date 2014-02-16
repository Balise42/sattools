#ifndef FORMULACREATIONMENU_H
#define FORMULACREATIONMENU_H 1

#include "execution.h"
#include "userinput.h"

/** presents a menu to the user that allows them to create a formula */
class FormulaCreationMenu{
  private:
    /** execution context */
    Execution * ex;
    /** number of variables of the formula */
    unsigned int n;
    /** arity of the clauses of the formula */
    unsigned int k;
    /** utility for user input processing */
    UserInput * ui;

  public:
    /** default constructor */
    FormulaCreationMenu(Execution * ex);
    /** destructor */
    ~FormulaCreationMenu();
    /** menu loop */
    void run();
    /** asks the user for the arity of the clauses*/
    void ask_k();
    /** asks the user for the number of variables */
    void ask_n();
    /** dispatches to formula creation from file */
    void create_file_formula();
    /** dispatches to formula creation from random parameters */
    void create_random_formula();
    /** dispatches to formula creation from assignments*/
    void create_max_formula();

};

#endif
