#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "assignment.h"
#include "userinputexception.h"

short& Assignment::operator[] (const int nIndex){
  return assignment[nIndex];
}

short Assignment::operator[] (const int nIndex) const{
    return assignment[nIndex];
}

void Assignment::clear(){
  assignment.clear();
}

bool Assignment::is_compatible(const Assignment & partial) const{
  int maxsize = std::max(partial.size(), size());
  for(int i = 0; i<maxsize; i++){
    if(partial[i] == -1){
      continue;
    }
    if(partial[i] != assignment[i]){
      return false;
    }
  }
  return true;
}

Assignment::Assignment():assignment(std::vector<short>(0)){
}

Assignment::Assignment(int n):assignment(std::vector<short>(n, -1)){
}

Assignment::Assignment(std::vector<short> assignment):assignment(assignment){
}

void Assignment::set_assignment(std::string s){
  std::vector<short> a = std::vector<short>(0);
  for(const auto & ch : s){
    if(ch == '0'){
      a.push_back(0);
    }
    else if(ch == '1'){
      a.push_back(1);
    }
    else{
      throw std::invalid_argument("Invalid assignment");
    }
  }
  assignment = a;
}

Assignment::iterator Assignment::begin(){
  return assignment.begin();
}

Assignment::iterator Assignment::end(){
  return assignment.end();
}

Assignment::const_iterator Assignment::begin() const{
  return assignment.begin();
}

Assignment::const_iterator Assignment::end() const{
  return assignment.end();
}

unsigned int Assignment::size() const{
  return assignment.size();
}


std::ostream& operator<<(std::ostream& out, const Assignment & as){
  for(const auto & var : as){
    out << var;
  }
  out << std::endl;
  return out;
}

std::istream &operator>>(std::istream &in, Assignment & as){
  std::string s;
  in >> s;
  as.set_assignment(s);
  return in;
}

bool operator< (const Assignment & lhs, const Assignment & rhs){
  return (lhs.assignment < rhs.assignment);
}

bool operator==(const Assignment & lhs, const Assignment & rhs){
  return (lhs.assignment == rhs.assignment);
}
