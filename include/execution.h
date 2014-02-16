#ifndef EXECUTION_H
#define EXECUTION_H 1

#include <vector>
#include <string>
#include "cnfformula.h"
#include "ppz.h"

/** Manages a full execution (creation of a formula, processing of the formula) */
class Execution {
  private:
    /** formula to process */
    CNFFormula * f;
    /** backup copy of the formula at the time of creation */
    CNFFormula * originalf;
    /** ppz algorithm */
    Ppz * ppz;
    /** number of variables */
    unsigned int n;
    /** arity of a clause */
    unsigned int k;
    /** has the formula been initialized? */
    bool formula_init;
    /** has the ppz object been initialized? */
    bool ppz_init;

  public:
    /** standard default constructor */
    Execution();
    /** standard destructor */
    ~Execution();
    /** creates a formula from a file */
    void get_file_formula(std::string filename, unsigned int k);
    /** creates a random formula */
    void get_random_formula(unsigned int n, unsigned int k, unsigned int p);
    /** creates a max formula from assignments */
    void get_max_formula(unsigned int n, unsigned int k, std::vector<assignment> &as);
    /** solve the formula by bruteforce*/
    void bruteforce();
    /** executes a full ppz run on the formula */
    void ppzfull();
    /** executes a full ppz run with oracle on the formula */
    void ppzfulloracle();
    /** executes a random ppz run on the formula */
    void ppzrandom();
    /** saves the formula to file */
    void save(std::string filename);
    /** getter for formula_init field */
    bool is_formula_init();
    /** resets the ppz object to clean state */
    void clearppz();
    /** resets the ppz object to clean state and the formula to original formula */
    void restart();
    /** prints the formula */
    void print_formula();
    /** prints the ppz stats */
    void print_ppz();
};

#endif
