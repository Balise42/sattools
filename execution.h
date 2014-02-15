#ifndef EXECUTION_H
#define EXECUTION_H 1

#include <vector>
#include <string>
#include "cnfformula.h"
#include "ppz.h"

class Execution {
  private:
    CNFFormula * f;
    CNFFormula * originalf;
    Ppz * ppz;
    unsigned int n;
    unsigned int k;
    bool formula_init;

  public:
    Execution();
    ~Execution();
    void get_file_formula(std::string filename, unsigned int k);
    void get_random_formula(unsigned int n, unsigned int k, unsigned int p);
    void get_max_formula(unsigned int n, unsigned int k, std::vector<assignment> &as);
    void bruteforce();
    void ppzfull();
    void ppzfulloracle();
    void ppzrandom();
    void save(std::string filename);
    bool is_formula_init();
};

#endif
