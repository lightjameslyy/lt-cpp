.PHONY: clean all

include ../../make.inc

INC = -I.
LDLIBS = -lpthread

SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

#TARGETS = $(patsubst %.cpp, %.bin, $(SRCS))
TARGETS = main.bin 

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

#%.bin: %.o
#	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	
all: $(TARGETS)

main.bin: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(TARGETS)

