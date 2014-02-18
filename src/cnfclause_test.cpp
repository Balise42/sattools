/* Unit tests for cnf_clause*/
#include "cnfclause.h"
#include "structs.h"
#include "gtest/gtest.h"
#include <vector>

TEST(CNFClause, create_empty_clause){
  CNFClause c;
  EXPECT_EQ(c.size(), 0);
}

TEST(CNFClause, create_clause_literal){
  literal l1;
  l1.variable = 0;
  l1.value = 0;
  literal l2;
  l2.variable = 1;
  l2.value = 1;
  std::vector<literal> literals;
  literals.push_back(l1);
  literals.push_back(l2);
  CNFClause c(literals);
  EXPECT_EQ(c.size(), 2);
  EXPECT_EQ(c.getliteral(0).variable, l1.variable);
  EXPECT_EQ(c.getliteral(1).value, l2.value);
}

TEST(CNFClause, add_literal){
  CNFClause c;
  literal l1;
  l1.variable=5;
  l1.value=1;
  c.add_literal(l1);
  EXPECT_EQ(c.size(), 1);
  EXPECT_EQ(c.getliteral(0).variable, 5);
  EXPECT_EQ(c.getliteral(0).value, 1);
}

TEST(CNFClause, check_bitstring){
  literal l1;
  l1.variable = 0;
  l1.value = 0;
  literal l2;
  l2.variable = 1;
  l2.value = 1;
  std::vector<literal> literals;
  literals.push_back(l1);
  literals.push_back(l2);
  CNFClause c(literals);
  std::vector<short> bitstring;
  bitstring.push_back(0);
  bitstring.push_back(1);
  EXPECT_TRUE(c.check_bitstring(bitstring));
  bitstring[0] = 1;
  EXPECT_TRUE(c.check_bitstring(bitstring));
  bitstring[1] = 0;
  EXPECT_FALSE(c.check_bitstring(bitstring));
  literal l3;
  l3.variable=2;
  l3.value = 0;
  c.add_literal(l3);
  EXPECT_TRUE(c.check_bitstring(bitstring));
}

TEST(CNFClause, test_iterators){
  literal l1;
  l1.variable = 0;
  l1.value = 0;
  literal l2;
  l2.variable = 1;
  l2.value = 1;
  std::vector<literal> literals;
  literals.push_back(l1);
  literals.push_back(l2);
  CNFClause c(literals);
  auto it = c.begin();
  EXPECT_EQ(it->value, 0);
  it++;
  EXPECT_EQ(it->value, 1);
  it++;
  EXPECT_EQ(it, c.end());
}
