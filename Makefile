CPP=clang++
CPPFLAGS=-Wall -W -Wextra -std=c++11 -ggdb
TARGETS=generate_sat_tool ppz_tool
GENERATE_OBJECTS=cnfclause.o cnfformula.o generate_sat_tool.o satgenerator.o
PPZ_OBJECTS=cnfclause.o cnfformula.o satgenerator.o ppz.o ppz_tool.o
OBJS=$(GENERATE_OBJECTS) $(PPZ_OBJECTS)

all: $(TARGETS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $<

generate_sat_tool: $(GENERATE_OBJECTS)
	$(CPP) $(CPPFLAGS) $(GENERATE_OBJECTS) -o $@

ppz_tool: $(PPZ_OBJECTS)
	$(CPP) $(CPPFLAGS) $(PPZ_OBJECTS) -o $@

clean:
	-rm -f $(OBJS) $(TARGETS)
