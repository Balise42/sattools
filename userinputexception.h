#ifndef USERINPUTEXCEPTION_H
#define USERINPUTEXCEPTION_H 1
#include <stdexcept>
#include <string>

class UserInputException : public std::invalid_argument{
  public:
    UserInputException(const std::string & message):std::invalid_argument(message){};
};

#endif
