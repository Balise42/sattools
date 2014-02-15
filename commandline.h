#ifndef COMMANDLINE_H
#define COMMANDLINE_H 1
#include <string>
#include <boost/program_options.hpp>
#include "cnfformula.h"
#include "ppz.h"

namespace po = boost::program_options;

class CommandLine{
  private:
    bool formula_init;
    CNFFormula * f;
    Ppz * ppz;
    unsigned int n;
    unsigned int k;
    std::string savefilename;
    po::options_description * desc;
    po::variables_map * vm;

  public:
    CommandLine(int argc, char ** argv);
    ~CommandLine();
    void parse_and_exec();
    void print_help();
    void parse_file_options();
    void parse_random();
    void parse_max();
    void get_file_formula(std::string filename, unsigned int k);
    void get_random_formula(unsigned int n, unsigned int k, unsigned int p);
    void get_max_formula(unsigned int n, unsigned int k, std::vector<assignment> &as);
    void bruteforce();
    void ppzfull();
    void ppzfulloracle();
    void ppzrandom();
};

#endif
