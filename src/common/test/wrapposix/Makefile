# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I../..
LDFLAGS = 
LDPATH = 
VPATH = ../..

PROGS =	hole seek mycat mywrite

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

hole: hole.o wrapposix.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

seek: seek.o wrapposix.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mycat: mycat.o wrapposix.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mywrite: mywrite.o wrapposix.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


