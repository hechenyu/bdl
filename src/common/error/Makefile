# Makefile

RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++11
INCLUDE = -I../
LDFLAGS = 
LDPATH = 
VPATH = ..

PROGS =	test_err_sys test_err_ret test_err_quit test_err_msg test_err_dump 

.PHONY: all
all: $(PROGS)
	@echo "build OK!"

clean:
	@$(RM) $(PROGS) *.o
	@echo "clean OK!"

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(INCLUDE)

test_err_sys: test_err_sys.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_err_ret: test_err_ret.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_err_quit: test_err_quit.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_err_msg: test_err_msg.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)

test_err_dump: test_err_dump.o error.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDPATH)


