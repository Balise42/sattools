#ifndef USERINPUTEXCEPTION_H
#define USERINPUTEXCEPTION_H 1
#include <stdexcept>
#include <string>

/** Exception for bad user input */
class UserInputException : public std::invalid_argument{
  public:
    UserInputException(const std::string & message):std::invalid_argument(message){};
};

#endif
