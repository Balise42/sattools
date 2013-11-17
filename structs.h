#ifndef STRUCTS_H
#define STRUCTS_H 1

#include <vector>

/*! \file */ 

/**represents a literal*/
struct literal{
  /** id of the variable: x1...xn represented by 0...n-1*/
  int variable;
  /** value of the variable - 0 if false, 1 if true */
  short value;
};

/** an assignment is a vector of values, indexed by the variable id */
typedef std::vector<short> assignment;

#endif
