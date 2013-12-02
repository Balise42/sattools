#ifndef PPZRUNSTATS_H
#define PPZRUNSTATS_H 1

#include <climits>

class PpzRunStats {
  private:
    void updateminmax(unsigned int tmp, unsigned int & maxforced, unsigned int & minforced, unsigned int & total);
  public:
    unsigned int all_cases;
    unsigned int satisfying_cases;
    unsigned int forced_a;
    unsigned int maxforced_a;
    unsigned int minforced_a;
    unsigned int forced_s;
    unsigned int maxforced_s;
    unsigned int minforced_s;
    unsigned int forced_u;
    unsigned int maxforced_u;
    unsigned int minforced_u;
    unsigned int tmpforced;

    PpzRunStats();
    friend std::ostream & operator<<(std::ostream & out, const PpzRunStats & stats);

    void tally_stats(bool satisfying);
};

#endif
