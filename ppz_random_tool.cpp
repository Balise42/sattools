#include "randomsatgenerator.h"
#include "cnfformula.h"
#include "ppz.h"

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

  RandomSatGenerator * satgen = new RandomSatGenerator(n, k);
  CNFFormula f = satgen->generate_sat();
  f.bruteforce_solve_sat();
  cout << f;
  Ppz * ppz = new Ppz(&f);
  ppz->full_solve_ppz();
  ppz->full_solve_ppz(true);
  cout << *ppz;
}
