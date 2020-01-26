.PHONY: clean all

RM = rm -rf
AR = ar rv
MAKE = make
CXX = g++
CXXFLAGS = -O3 -std=c++11 -g -fPIC
ECXXFLAGS = 
INC = 
LDFLAGS = 
LDLIBS =

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

#TARGETS = $(patsubst %.cpp, %.exe, $(SRCS))
TARGETS = liblnp.a liblnp.so

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

all: $(TARGETS)

liblnp.a: $(OBJS)
	$(AR) $@ $^

liblnp.so: $(OBJS)
	$(CXX) -fPIC -shared -o $@ $^ $(LDFLAGS) $(LDLIBS)
	
clean:
	$(RM) $(OBJS) $(TARGETS)

