CPP=clang++
CPPFLAGS=-Wall -W -Wextra -std=c++11 -ggdb
TARGETS=generate_sat_tool ppz_tool ppz_random_tool
GENERATE_OBJECTS=cnfclause.o cnfformula.o generate_sat_tool.o satgenerator.o maxsatgenerator.o
PPZ_OBJECTS=cnfclause.o cnfformula.o satgenerator.o ppz.o ppz_tool.o maxsatgenerator.o
PPZ_RANDOM_OBJECTS=cnfclause.o cnfformula.o satgenerator.o ppz.o randomsatgenerator.o ppz_random_tool.o
OBJS=$(GENERATE_OBJECTS) $(PPZ_OBJECTS)
# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = /usr/src/gtest
GTEST_CPPFLAGS += -I$(GTEST_DIR)/include
TESTS = cnfclause_test
GTEST_HEADERS = /usr/include/gtest/*.h /usr/include/gtest/internal/*.h

all: $(TARGETS) $(TESTS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $<

generate_sat_tool: $(GENERATE_OBJECTS)
	$(CPP) $(CPPFLAGS) $(GENERATE_OBJECTS) -o $@

ppz_tool: $(PPZ_OBJECTS)
	$(CPP) $(CPPFLAGS) $(PPZ_OBJECTS) -o $@

ppz_random_tool: $(PPZ_RANDOM_OBJECTS)
	$(CPP) $(CPPFLAGS) $(PPZ_RANDOM_OBJECTS) -o $@

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

cnfclause_test.o: cnfclause_test.cpp
	$(CPP) $(CPPFLAGS) $(GTEST_CPPFLAGS) -c $<

cnfclause_test: cnfclause.o cnfclause_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ -lpthread

cnfformula_test.o: cnfformula_test.cpp
	$(CPP) $(CPPFLAGS) $(GTEST_CPPFLAGS) -c $<

cnfformula_test: cnfformula.o cnfclause.o cnfformula_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ -lpthread
