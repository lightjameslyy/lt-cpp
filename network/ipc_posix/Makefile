.PHONY: clean all

RM = rm -rf
AR = ar rv
MAKE = make
CXX = g++
CXXFLAGS = -O3 -std=c++11 -g -fPIC
ECXXFLAGS = 
INC = -I..
LDFLAGS = ../liblnp.a
LDLIBS = -lrt

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGETS = $(patsubst %.cpp, %.exe, $(SRCS))

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

%.exe: %.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

all: $(TARGETS)

clean:
	$(RM) $(OBJS) $(TARGETS)

