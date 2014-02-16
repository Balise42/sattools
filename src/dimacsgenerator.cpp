#include "dimacsgenerator.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

DimacsGenerator::DimacsGenerator(std::ifstream & file, int k):SatGenerator(0,k){
  unsigned int nn, m;
  if(file.is_open()){
    std::string line;
    bool reading_clauses = false;
    while(getline(file, line)){
      std::stringstream ss;
      ss << line;
      if(!reading_clauses){
        char c;
        ss >> c;
        if(c == 'c'){
          continue;    
        }
        else if(c == 'p'){
          std::string cnf;
          ss >> cnf;
          ss >> nn;
          ss >> m;
          formula = new CNFFormula(nn, k);
          reading_clauses = true;
        }
        else{
          return;
        }
      }
      else{
        std::vector<int> clausespec;
        int lit;
        while(1){
          ss >> lit;
          if(lit == 0){
            break;
          }
          clausespec.push_back(lit);
        }
        CNFClause clause(clausespec);
        formula->add_clause(clause);
      }
    }
  }
  else{
    return;
  }
}

CNFFormula DimacsGenerator::generate_sat(){
  return *formula;
}
