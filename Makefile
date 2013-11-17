CPP=clang++
CPPFLAGS=-Wall -W -Wextra -std=c++11 -ggdb
TARGETS=generate_sat_tool
GENERATE_OBJECTS=cnfclause.o cnfformula.o generate_sat_tool.o satgenerator.o
OBJS=$(GENERATE_OBJECTS)

all: $(TARGETS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $<

generate_sat_tool: $(GENERATE_OBJECTS)
	$(CPP) $(CPPFLAGS) $(GENERATE_OBJECTS) -o $@

clean:
	-rm -f $(OBJS) $(TARGETS)
