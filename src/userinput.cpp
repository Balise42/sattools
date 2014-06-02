/* Basic structures: manages user input from interactive mode/console */
#include <iostream>
#include <sstream>
#include <string>
#include "userinput.h"
#include "userinputexception.h"
#include "structs.h"

char UserInput::getchar(std::string  prompt){
  std::cout << prompt << std::endl;
  std::cout << "> ";
  std::string input = "";
  std::getline(std::cin, input);
  if(input.length() == 1){
    return input[0];
  }
  throw UserInputException("Single character expected");
}

int UserInput::getint(std::string  prompt){
  std::cout << prompt << std::endl;
  std::cout << "> ";
  std::string input = "";
  std::getline(std::cin, input);
  std::stringstream str(input);
  int num;
  if(str >> num && str.peek() == EOF){
    return num;
  }
  throw UserInputException("Integer expected");
}

std::string UserInput::getstring(std::string  prompt){
  std::cout << prompt << std::endl;
  std::cout << "> ";
  std::string input = "";
  getline(std::cin, input);
  return input;
}

Assignment UserInput::getassignment(unsigned int n, std::string  prompt){
  std::cout << prompt << std::endl;
  std::cout << " > ";
  std::string input = "";
  getline(std::cin, input);
  if(input.length() != n){
    throw UserInputException("An assignment must contain exactly n characters");
  }
  Assignment a;
  a.set_assignment(input);
  return a;
}
