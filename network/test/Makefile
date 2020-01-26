.PHONY: clean all

RM = rm -rf
AR = ar rv
MAKE = make
CXX = g++
CXXFLAGS = -O3 -std=c++11 -g
ECXXFLAGS = 
INC = -I..
LDFLAGS = ../liblnp.a
LDLIBS = -lgtest -lgtest_main

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

#TARGETS = $(patsubst %.cpp, %.exe, $(SRCS))
TARGETS = test.exe

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

test.exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	
all: $(TARGETS)

clean:
	$(RM) $(OBJS) $(TARGETS)

