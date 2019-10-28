.PHONY: clean all

include ../../make.inc

CXX = g++
CXXFLAGS = -std=c++11 
ECXXFLAGS = 
INC = -I$(BOOST_HOME)/include -I.
LDFLAGS = -L$(BOOST_HOME)/lib
LDLIBS = 

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGETS = $(patsubst %.cpp, %.exe, $(SRCS))

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

%.exe: %.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)

