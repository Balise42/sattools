#ifndef USERINPUT_H
#define USERINPUT_H 1

#include <string>
#include "structs.h"

class UserInput{
  public:
    char getchar();
    int getint();
    std::string getstring();
    assignment getassignment(unsigned int n);
};

#endif
