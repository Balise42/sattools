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

assignment UserInput::getassignment(unsigned int n, std::string  prompt){
  std::cout << prompt << std::endl;
  std::cout << " > ";
  std::string input = "";
  getline(std::cin, input);
  if(input.length() != n){
    throw UserInputException("An assignment must contain exactly n characters");
  }
  assignment a;
  // checks bit by bit that the assignment is a set of 0s and 1s - creates the assignment 
  for(const auto & ch : input){
    if(ch == '0'){
      a.push_back(0);
    }
    else if(ch == '1'){
      a.push_back(1);
    }
    else{
      throw UserInputException("An assignment must only contain 0s and 1s");
    }
  }
  return a;
}
