/* Basic structures: Small data structures that do not need any methods attached to them */
#ifndef STRUCTS_H
#define STRUCTS_H 1

#include <vector>

/*! \file */ 

/**represents a literal*/
struct literal{
  /** id of the variable: x1...xn represented by 0...n-1*/
  unsigned int variable;
  /** value of the variable - 0 if false, 1 if true */
  short value;
};

#endif
