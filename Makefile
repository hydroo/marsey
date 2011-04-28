CXX = g++
INCLUDE =
CXXFLAGS = -Wall -g -std=c++0x -DDEBUG $(INCLUDE)
#CXXFLAGS = -Wall -std=c++0x $(INCLUDE)
LN = g++
LIBS =
LFLAGS = $(LIBS)

BINARY = marsey

OBJECTS = main.o graph.o
INCLUDES = graph.hpp debug.hpp
SOURCES = main.cpp graph.cpp


all: dep bin

bin: $(OBJECTS)
	$(LN) $(LFLAGS) -o $(BINARY) $^
	@echo ""

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

dep: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $^ > .depend

-include .depend

.PHONY: clean
clean:
	-rm -f marsey *.o *.hpp.gch

