#ifndef PPZRUNSTATS_H
#define PPZRUNSTATS_H 1

#include <climits>

class PpzRunStats {
  private:
    /** update min and max number of variables forced after one run of the algorithm */
    void updateminmax(unsigned int tmp, unsigned int & maxforced, unsigned int & minforced, unsigned int & total);
  public:
    /** total number of tries */
    unsigned int all_cases;
    /** total number of satisfying cases */
    unsigned int satisfying_cases;
    /** total number of forced variables for all results */
    unsigned int forced_a;
    /** maximum number of forced variables for all results */
    unsigned int maxforced_a;
    /** minimum number of forced variables for all results */
    unsigned int minforced_a;
    /** total number of forced variables for satisfying assignments */
    unsigned int forced_s;
    /** maximum number of forced variables for satisfying assignments */
    unsigned int maxforced_s;
    /** minimum number of forced variables for satisfying assignments */
    unsigned int minforced_s;
    /** total number of forced variables for unsatisfying runs */
    unsigned int forced_u;
    /** maximum number of forced variables for unsatisfying runs */
    unsigned int maxforced_u;
    /** minimum number of forced variables for unsatisfying runs */
    unsigned int minforced_u;

    /** default constructor*/
    PpzRunStats();
    /** prettyprint */
    friend std::ostream & operator<<(std::ostream & out, const PpzRunStats & stats);

    /** adds the current number of forced variables to satisfying run stats */
    void record_success(unsigned int forced);
    /** adds the current number of forced variables to unsatisfying run stats */
    void record_failure(unsigned int forced);
};

#endif
