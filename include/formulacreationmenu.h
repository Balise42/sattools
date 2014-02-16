#ifndef FORMULACREATIONMENU_H
#define FORMULACREATIONMENU_H 1

#include "userinput.h"
#include "cnfformula.h"

/** presents a menu to the user that allows them to create a formula */
class FormulaCreationMenu{
  private:
    /** number of variables of the formula */
    unsigned int n;
    /** arity of the clauses of the formula */
    unsigned int k;
    /** utility for user input processing */
    UserInput * ui;
    /** asks the user for the arity of the clauses*/
    void ask_k();
    /** asks the user for the number of variables */
    void ask_n();
    /** dispatches to formula creation from file */
    void create_file_formula(CNFFormula & f) ;
    /** dispatches to formula creation from random parameters */
    void create_random_formula(CNFFormula & f) ;
    /** dispatches to formula creation from assignments*/
    void create_max_formula(CNFFormula & f) ;

  public:
    /** default constructor */
    FormulaCreationMenu();
    /** destructor */
    ~FormulaCreationMenu();
    /** menu loop */
    bool run(CNFFormula & f);

};

#endif
