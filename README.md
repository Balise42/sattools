#sattools

## Description of the project
SAT tools - small SAT formula generator from assignments, some algorithms. NOT intended for efficiency.

I'm working on a research project around SAT - and I need a few tools around that, including simulation of algorithms I'm currently working on with different variants. I'm trying to get my code as generic and proper/usable as possible so that it may be used by other people!

Said algorithms are, however, much more on the theoretic/exponential bounds side - this is typically NOT a SAT solver that will solve anything "big" in any remotely reasonable time. We're talking Omega(2^n) time here. Don't expect better.

## Some context
The PPZ algorithm was first described in the paper Satisfiability Coding Lemma by Paturi, Pudlak and Zane (see http://cm.bell-labs.com/who/francis/papers/focs97.ps). The "random" implementation is closest to the spirit of this algorithm - it picks a random permutation and a random codeword and tries them against the formula, retrying until it finds something or until it gets to a pre-set number of iterations. Our "full" implementation allows us to check for all the permutations and all the codewords. Our "full with oracle" implementation allows us to check for all the permutations and all the codewords, with the twist that, if both literals of a variable are satisfying, we always set that variable to 0. This implementation actually relies on a bruteforce solving of the assignments - it is NOT designed for any solving per se, but to get statistics and insight about the algorithm for different formulas.

## Executable options
  -h [ --help ]           Print help message
  -n [ --n ] arg          Number of variables
  -k [ --k ] arg          Arity of a clause
  -f [ --file ] arg       Get formula from file
  -r [ --random ] arg     Get random formula with given random range
  -m [ --max ]            Get maximum formula from a set of assignments
  -a [ --assignment ] arg List of assignments for -m
  -i [ --interactive ]    Interactive mode
  --bruteforce            Solve by bruteforce - warning, all case exponential 
                          time algorithm!
  --ppzfull               Solve by full ppz - warning, all case 
                          superexponential time algorithm!
  --ppzfulloracle         Solve by full ppz with oracle - warning, all case 
                          superexponential time algorithm!
  --ppzrandom             Solve by random ppz - warning, worst case exponential
                          time algorithm!
  -s [ --save ] arg       Save the formula in DIMACS format in given file. 
                          Default is save in 'formula.cnf'.

## Description of the source files
* Main executable
  * sattools.cpp: just invokes the command line parsing
  * commandline.cpp: command line parsing and dispatching
  * interactivemode.cpp: tiny console for execution
  * execution.cpp: dispatcher of commands to the core algorithms
* Basic structures
  * structs.h: small data structures that do not need any methods attached to them (namely, literals and assignments)
  * cnfclause.cpp: a CNF clause (disjunction of literals)
  * cnfformula.cpp: a CNF formula. Also contains algorithms for bruteforce solving and checking for frozen variables.
  * ppz.cpp: PPZ algorithm implementations (full, full with oracle, random)
  * ppzrunstats.cpp: PPZ statistics for a run (to compare with/without oracle)
  * userinput.cpp: manages user input from interactive mode/console
* Formula generators
  * satgenerator.cpp: parent class for the other generators
  * dimacsgenerator.cpp: reads a formula from a simplified DIMACS file (see http://www.satcompetition.org/2009/format-benchmarks2009.html)
  * maxsatgenerator.cpp: create a formula from a set of satisfying assignments by checking all possible clauses and inserting the ones that are compatible with the satisfying assignments.
  * randomsatgenerator.cpp: create a formula by generating all clauses and picking some of them according to the given probability
* Menus
  * formulacreationmenu.cpp: menu used by the interactive mode to create a formula
  * executionmenu.cpp: menu used to process the created formula in the interactive mode
* Miscellaneous tests and temporary executables
  * cnfclause_test.cpp, cnfformula_test.cpp: unit tests for cnfclause and cnfformula
  * dimacs_tool.cpp, generate_sat_tool.cpp,ppz_random_tool.cpp,ppz_tool.cpp: miscellaneous temporary executables used in previous versions instead of the generic "sattools" executable.
