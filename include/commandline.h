#ifndef COMMANDLINE_H
#define COMMANDLINE_H 1
#include <string>
#include <boost/program_options.hpp>
#include "cnfformula.h"
#include "ppz.h"
#include "execution.h"

namespace po = boost::program_options;

class CommandLine{
  private:
    po::options_description * desc;
    po::variables_map * vm;
    Execution * execution;

  public:
    CommandLine(int argc, char ** argv);
    ~CommandLine();
    void parse_and_exec();
    void print_help();
    void parse_file_options();
    void parse_random();
    void parse_max();
};

#endif
