/* Main executable - just invokes the command line parsing */
#include "commandline.h"

int main(int argc, char** argv){
  CommandLine * cl = new CommandLine(argc, argv);
  cl->parse_and_exec();
  return 0;
}
