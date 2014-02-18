/* Unit tests for cnfformula and solvedcnf*/
#include "cnfformula.h"
#include "cnfclause.h"
#include "solvedcnf.h"
#include "structs.h"
#include "gtest/gtest.h"
#include <vector>

TEST(CNFFormula, create_empty){
  CNFFormula f(5,3);
  EXPECT_EQ(f.get_n(), 5);
  EXPECT_EQ(f.get_m(), 0);
}

class CNFFormulaTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
      literal l;
      CNFClause c;
      std::vector<CNFClause> clauses;
      l.variable=0;
      l.value = 0;
      c.add_literal(l);
      l.variable=2;
      l.value=1;
      c.add_literal(l);
      l.variable=3;
      l.value=0;
      c.add_literal(l);
      clauses.push_back(c);
      f = CNFFormula(5,3,clauses);
    }
    CNFFormulaTest():f(CNFFormula(0,0)){};
    CNFFormula f;
};

TEST_F(CNFFormulaTest, create_with_clauses){
  EXPECT_EQ(f.get_m(), 1);
  EXPECT_EQ(f.begin()->getliteral(1).variable, 2);
}

TEST(CNFFormula, bruteforce_solve_sat){
  literal l;
  CNFClause c;
  std::vector<CNFClause> clauses;
  l.variable=0;
  l.value = 0;
  c.add_literal(l);
  l.variable=2;
  l.value=1;
  c.add_literal(l);
  l.variable=1;
  l.value=0;
  c.add_literal(l);
  clauses.push_back(c);
  CNFFormula f(3,3,clauses);
  SolvedCNF solf(f);
  EXPECT_EQ(solf.get_satisfying_assignments().size(), 7);
}

TEST(CNFFormula, check_bitstring){
  literal l;
  CNFClause c;
  std::vector<CNFClause> clauses;
  l.variable=0;
  l.value = 0;
  c.add_literal(l);
  l.variable=2;
  l.value=1;
  c.add_literal(l);
  l.variable=1;
  l.value=0;
  c.add_literal(l);
  clauses.push_back(c);
  CNFFormula f(3,3,clauses);
  SolvedCNF solf(f);
  std::vector<assignment> assg = solf.get_satisfying_assignments();
  for(const auto & it : assg){
    EXPECT_TRUE(f.check_bitstring(it));
  }
  assignment assfalse;
  assfalse.push_back(1); assfalse.push_back(1); assfalse.push_back(0);
  EXPECT_FALSE(f.check_bitstring(assfalse));
}

