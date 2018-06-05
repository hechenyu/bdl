# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I../
LDFLAGS = 
LDPATH = 
VPATH = ..

PROGS =	datafile_header_size

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

datafile_header_size: datafile_header_size.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

