#include <fstream>
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
  ifstream file(filename);
  if(file.is_open()){
    DimacsGenerator dg(file, k);
    cout << dg.generate_sat() << endl;
  }
}

