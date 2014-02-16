#ifndef COMMANDLINE_H
#define COMMANDLINE_H 1
#include <string>
#include <boost/program_options.hpp>
#include "cnfformula.h"
#include "ppz.h"

namespace po = boost::program_options;

/** Command line parser and dispatcher */
class CommandLine{
  private:
    /** option description for the command line */
    po::options_description * desc;
    /** map options/value from the command line */
    po::variables_map * vm;

  public:
    /** construct an object from the command line arguments */
    CommandLine(int argc, char ** argv);
    /** standard destructor */
    ~CommandLine();
    /** reads the options of the command line and dispatches to the correct helper functions */
    void parse_and_exec();
    /** prints help (summary of the options) */
    void print_help();
    /** gets the filename and arity of clauses, dispatches to Execution */
    void parse_file_options(CNFFormula & f);
    /** gets the parameters for the random formula generator, dispatches to Execution */
    void parse_random(CNFFormula & f);
    /** gets the parameter for the "max formula" generator, dispatches to Execution */
    void parse_max(CNFFormula & f);
};

#endif
