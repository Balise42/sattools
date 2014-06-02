/* DEPRECATED - proof of concept for ppz */
#include "maxsatgenerator.h"
#include "cnfformula.h"
#include "ppz.h"
#include <cmath>
#include "solvedcnf.h"

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
  vector<Assignment> assignments(nsat, Assignment(0));
  for(unsigned int i = 0; i<nsat; i++){
    string assignment;
    cout << "Assignment: " << endl;
    cout << "> ";
    cin >> assignments[i];
  }

  MaxSatGenerator * satgen = new MaxSatGenerator(n, k, assignments);
  CNFFormula f;
  satgen->generate_sat(f);
  SolvedCNF solf(f);
  cout << solf;
  Ppz * ppz = new Ppz(f);
//  ppz->full_solve_ppz();
//  ppz->full_solve_ppz(true);
//  cout << *ppz;
  double limit = pow(2, n-1.0/k);
  ppz->random_solve_ppz(limit);
}
