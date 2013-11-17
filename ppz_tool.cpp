#include "satgenerator.h"
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

  //number of satisfying assignments
  unsigned int nsat;
  cout << "How many assignments?" << endl << "> ";
  cin >> nsat;

  //get the assignments
  vector<vector<short> > assignments(nsat, vector<short>(n, 0));
  for(unsigned int i = 0; i<nsat; i++){
    string assignment;
    cout << "Assignment: " << endl;
    cout << "> ";
    cin >> assignment;
    unsigned int pos = 0;
    for(auto bit : assignment){
      if(pos >= n){
        break;
      }
      if(bit == '0'){
        assignments[i][pos] = 0;
      }
      else if (bit == '1'){
        assignments[i][pos] = 1;
      }
      else{        cout << "Invalid character, exiting." << endl;
        return -1;
      }
      pos++;
    }
  }

  SatGenerator * satgen = new SatGenerator(n, k, nsat, assignments);
  CNFFormula f = satgen->generate_sat();
  cout << f;
  Ppz * ppz = new Ppz(&f);
  ppz->solve_ppz();
  cout << *ppz;
}
