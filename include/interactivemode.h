#ifndef INTERACTIVEMODE_H
#define INTERACTIVEMODE_H 1

#include "execution.h"

/** interactive mode (console) */
class InteractiveMode{
  private:
    /** execution context */
    Execution * ex;

  public:
    /** default constructor */
    InteractiveMode();
    /** destructor */
    ~InteractiveMode();
    /** displays the menus */
    void start();
};

#endif
