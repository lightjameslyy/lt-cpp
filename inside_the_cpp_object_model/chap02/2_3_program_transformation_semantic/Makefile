.PHONY: clean all

RM = rm -rf
AR = ar rv
MAKE = make
CXX = g++
CXXFLAGS = -std=c++11 -g
ECXXFLAGS = 
LDFLAGS = 
LDLIBS = 

CXXFLAGS += -O3
#CXXFLAGS += -fopenmp
#INC += -I..

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

