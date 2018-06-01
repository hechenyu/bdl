# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I..
LDFLAGS = 
LDPATH = 
VPATH = ..

PROGS =	ceil_to_align_at

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

ceil_to_align_at: ceil_to_align_at.o 
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

