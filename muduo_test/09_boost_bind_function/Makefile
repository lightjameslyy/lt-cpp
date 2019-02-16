.PHONY: clean all

RM = rm -rf
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 
ECXXFLAGS = 
INC = -I.
LDFLAGS = -lpthread
LDLIBS = 

SRCS = $(wildcard *.cpp)

EXESRCS = $(wildcard *_test.cpp)

PURESRCS = $(filter-out $(EXESRCS), $(SRCS))

OBJS = $(patsubst %.cpp, %.o, $(SRCS))
PUREOBJS = $(patsubst %.cpp, %.o, $(PURESRCS))

TARGETS = $(patsubst %.cpp, %.bin, $(EXESRCS))
#TARGETS = bf_test.bin \
#		  Thread_test.bin

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

%.bin: %.o $(PUREOBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

#bf_test.bin: bf_test.o
#	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

#Thread_test.bin: Thread.o Thread_test.o
#	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	
all: $(TARGETS)

clean:
	$(RM) $(OBJS) $(TARGETS)

