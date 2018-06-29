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
	@$(RM) $(PROGS) *.o file.hole test.txt
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

hole: hole.o wrapstdio.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

seek: seek.o wrapstdio.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mycat: mycat.o wrapstdio.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

mywrite: mywrite.o wrapstdio.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


