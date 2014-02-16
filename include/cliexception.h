#ifndef CLIEXCEPTION_H
#define CLIEXCEPTION_H 1
#include <exception>
#include <string>

class CLIException : public std::logic_error{
  public:
    CLIException(const std::string & message):std::logic_error(message){};
};

#endif
