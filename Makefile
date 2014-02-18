CPP=clang++
INCLUDEDIR=./include
SRCDIR=./src
BUILDDIR=./build
CPPFLAGS=-Wall -W -Wextra -std=c++11 -ggdb -I$(INCLUDEDIR)
TARGETS=$(addprefix tests/,generate_sat_tool ppz_tool ppz_random_tool dimacs_tool) sattools
GENERATE_OBJECTS=$(addprefix $(BUILDDIR)/,cnfclause.o cnfformula.o generate_sat_tool.o satgenerator.o maxsatgenerator.o solvedcnf.o)
PPZ_OBJECTS=$(addprefix $(BUILDDIR)/,cnfclause.o cnfformula.o satgenerator.o ppz.o ppz_tool.o maxsatgenerator.o ppzrunstats.o solvedcnf.o)
PPZ_RANDOM_OBJECTS=$(addprefix $(BUILDDIR)/,cnfclause.o cnfformula.o satgenerator.o ppz.o randomsatgenerator.o ppz_random_tool.o ppzrunstats.o solvedcnf.o)
DIMACS_OBJECTS=$(addprefix $(BUILDDIR)/,cnfclause.o cnfformula.o satgenerator.o dimacsgenerator.o dimacs_tool.o solvedcnf.o)
SATTOOLS_OBJECTS=$(addprefix $(BUILDDIR)/,cnfclause.o cnfformula.o satgenerator.o dimacsgenerator.o sattools.o ppz.o randomsatgenerator.o maxsatgenerator.o ppzrunstats.o commandline.o interactivemode.o formulacreationmenu.o userinput.o executionmenu.o solvedcnf.o)
OBJS=$(GENERATE_OBJECTS) $(PPZ_OBJECTS) $(DIMACS_OBJECTS) $(SATTOOLS_OBJECTS)
LIBS=-lboost_program_options
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = /usr/src/gtest
GTEST_CPPFLAGS += -I$(GTEST_DIR)/include
TESTS = tests/cnfclause_test tests/cnfformula_test
GTEST_HEADERS = /usr/include/gtest/*.h /usr/include/gtest/internal/*.h

all: $(TARGETS) $(TESTS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

tests/generate_sat_tool: $(GENERATE_OBJECTS)
	$(CPP) $(CPPFLAGS) $(GENERATE_OBJECTS) -o $@

tests/ppz_tool: $(PPZ_OBJECTS)
	$(CPP) $(CPPFLAGS) $(PPZ_OBJECTS) -o $@

tests/ppz_random_tool: $(PPZ_RANDOM_OBJECTS)
	$(CPP) $(CPPFLAGS) $(PPZ_RANDOM_OBJECTS) -o $@

tests/dimacs_tool: $(DIMACS_OBJECTS)
	$(CPP) $(CPPFLAGS) $(DIMACS_OBJECTS) -o $@

sattools: $(SATTOOLS_OBJECTS)
	$(CPP) $(CPPFLAGS) $(SATTOOLS_OBJECTS) -o $@ $(LIBS)

clean:
	-rm -f $(OBJS) $(TARGETS)

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CPP) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILDDIR)/cnfclause_test.o: $(SRCDIR)/cnfclause_test.cpp
	$(CPP) $(CPPFLAGS) $(GTEST_CPPFLAGS) -c $< -o $@

tests/cnfclause_test: $(BUILDDIR)/cnfclause.o $(BUILDDIR)/cnfclause_test.o  lib/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ -lpthread

tests/cnfformula_test.o: $(SRCDIR)/cnfformula_test.cpp
	$(CPP) $(CPPFLAGS) $(GTEST_CPPFLAGS) -c $<

tests/cnfformula_test: $(BUILDDIR)/cnfformula.o $(BUILDDIR)/cnfclause.o $(BUILDDIR)/solvedcnf.o $(BUILDDIR)/cnfformula_test.o lib/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ -lpthread

