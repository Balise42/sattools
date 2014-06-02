#ifndef USERINPUT_H
#define USERINPUT_H 1

#include <string>
#include "structs.h"
#include "assignment.h"

/** User input checking utility class*/
class UserInput{
  public:
    /** gets a char from std::cin */
    char getchar(std::string prompt);
    /** gets an int from std::cin */
    int getint(std::string prompt);
    /** gets a string from std::cin */
    std::string getstring(std::string prompt);
    /** gets an assignment from std::cin */
    Assignment getassignment(unsigned int n,std::string prompt);
};

#endif
