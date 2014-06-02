/* DEPRECATED - proof of concept for max sat generator*/
#include "maxsatgenerator.h"
#include "cnfformula.h"
#include "assignment.h"

int main(){
  using namespace std;
  //number of variables
  unsigned int n;
  cout << "How many variables?" << endl << "> ";
  cin >> n;

  //k-sat ; k=?
  unsigned int k;
  cout << "What's k?" << endl << endl << "> ";
  cin >> k;

  //number of satisfying assignments
  unsigned int nsat;
  cout << "How many assignments?" << endl << "> ";
  cin >> nsat;

  //get the assignments
  vector<Assignment> assignments(nsat, Assignment());
  for(unsigned int i = 0; i<nsat; i++){
    string assignment;
    cout << "Assignment: " << endl;
    cout << "> ";
    cin >> assignments[i];
  }

  MaxSatGenerator * satgen = new MaxSatGenerator(n, k, assignments);
  CNFFormula f;
  satgen->generate_sat(f);
  cout << f;
}
