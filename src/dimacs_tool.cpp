#include "dimacsgenerator.h"
#include <iostream>
#include <string>

int main(){
  using namespace std;
  string filename;
  cout << "Enter the file name." << endl << "> ";
  cin >> filename;
  int k;
  cout << "What is k in that file?" << endl << "> ";
  cin >> k;
  CNFFormula f;
  DimacsGenerator dg(filename, k);
  cout << dg.generate_sat(f) << endl;
  
}

