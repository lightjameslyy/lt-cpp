.PHONY: clean all

RM = rm -rf
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 
ECXXFLAGS = 
INC = -I.
LDFLAGS = -lpthread
LDLIBS = 

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGETS = $(patsubst %.cpp, %.bin, Thread_test.cpp)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

%.bin: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	
all: $(TARGETS)

clean:
	$(RM) $(TARGETS)

