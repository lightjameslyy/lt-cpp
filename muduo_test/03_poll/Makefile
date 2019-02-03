.PHONY: clean all

RM = rm -rf
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 
ECXXFLAGS = 
INC = 
LDFLAGS = 
LDLIBS = 

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

