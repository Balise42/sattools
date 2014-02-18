/* Formula generators:  reads a formula from a simplified DIMACS file (see http://www.satcompetition.org/2009/format-benchmarks2009.html) */
#include "dimacsgenerator.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "cnfformula.h"

DimacsGenerator::DimacsGenerator(std::string filename, unsigned int k):SatGenerator(0,k),filename(filename){
}

void DimacsGenerator::generate_sat(CNFFormula & f){
  char c;
  std::ifstream file(filename);
  std::string line;
  while(1){
    c = file.peek();
    if(!getline(file, line)){
      break;
    }
    if(c == 'c'){
      continue;
    }

    std::stringstream ss;
    ss << line;

    if(c == 'p'){
      std::string cnf;
      ss >> cnf;
      ss >> cnf;
      if(!(ss >> n)){
        throw std::invalid_argument("File is not a valid DIMACS file (header invalid)");
      }
      f = CNFFormula(n, k);
    }
    else{
      std::vector<int> clausespec;
      int lit;
      while(1){
        if(ss >> lit){
          if(lit == 0){
            break;
          }
          clausespec.push_back(lit);
        }
        else throw std::invalid_argument("File is not a valid DIMACS file (clause invalid)");
      }
      CNFClause clause(clausespec);
      f.add_clause(clause);
    }
  }
}
