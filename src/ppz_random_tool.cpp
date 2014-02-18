/* DEPRECATED - proof of concept for random sat generator*/
#include "randomsatgenerator.h"
#include <cmath>
#include "cnfformula.h"
#include "ppz.h"
#include "solvedcnf.h"

int main(){
  using namespace std;
  //number of variables
  unsigned int n;
  cout << "How many variables?" << endl << "> ";
  cin >> n;

  //k-sat ; k=?
  unsigned int k;
  cout << "What's k?" << endl << "> ";
  cin >> k;

  //probability of keeping a clause
  int prob;
  cout << "Probability range?" << endl << "> ";
  cin >> prob;

  RandomSatGenerator * satgen = new RandomSatGenerator(n, k, prob);
  CNFFormula f;
  satgen->generate_formula(f);
  SolvedCNF solf(f);
  cout << solf;
  Ppz * ppz = new Ppz(f);
//  ppz->full_solve_ppz();
//  ppz->full_solve_ppz(true);
  double limit = pow(2, n-1.0/k);
  ppz->random_solve_ppz(limit);
//  cout << *ppz;
}
