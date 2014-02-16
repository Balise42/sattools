#ifndef USERINPUT_H
#define USERINPUT_H 1

#include <string>
#include "structs.h"

/** User input checking utility class*/
class UserInput{
  public:
    /** gets a char from std::cin */
    char getchar();
    /** gets an int from std::cin */
    int getint();
    /** gets a string from std::cin */
    std::string getstring();
    /** gets an assignment from std::cin */
    assignment getassignment(unsigned int n);
};

#endif
