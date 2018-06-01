# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I../
LDFLAGS = 
LDPATH = 
VPATH = ..

PROGS =	data_file_header_size

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

data_file_header_size: data_file_header_size.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

