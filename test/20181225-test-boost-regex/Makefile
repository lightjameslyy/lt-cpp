.PHONY: clean all

include ../../make.inc

CXX = g++
CXXFLAGS = -std=c++11 
ECXXFLAGS = 
INC = -I$(BOOST_HOME)/include
LDFLAGS = -L$(BOOST_HOME)/lib
LDLIBS = -lboost_regex

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGETS = $(patsubst %.cpp, %.bin, $(SRCS))

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

%.bin: %.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)

