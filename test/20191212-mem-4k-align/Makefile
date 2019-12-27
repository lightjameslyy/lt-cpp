.PHONY: clean all

include ../../make.inc

CXXFLAGS += -O0

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

