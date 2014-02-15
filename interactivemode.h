#ifndef INTERACTIVEMODE_H
#define INTERACTIVEMODE_H 1

#include "execution.h"

class InteractiveMode{
  private:
    Execution * ex;

  public:
    InteractiveMode();
    ~InteractiveMode();
    void start();
};

#endif
