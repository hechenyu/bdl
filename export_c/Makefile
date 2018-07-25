
RM = rm -f
CREATE_SO = g++ -shared
CXX = g++
CXXFLAGS = -fPIC -Wall -g -DNDEBUG -std=c++11
INCLUDES = -I../src/io -I../src/dataset -I../src/indexfile -I../thirdparty/include/
LDFLAGS = -lbase_dataset_loader -lprotobuf-lite -lboost_filesystem -lboost_system
LDPATH = -L../lib -L../thirdparty/lib
VPATH = 

SOURCES = $(shell ls *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
DYNAMICLIB = libcbase_dataset_loader.so

all: $(DYNAMICLIB)
	@echo "DYNAMICLIB = $(DYNAMICLIB)" 

.PHONY: clean
clean:
	$(RM) $(DYNAMICLIB) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -o $@ -c $(CXXFLAGS) $(INCLUDES) $<

$(DYNAMICLIB): $(OBJECTS)
	$(CREATE_SO) -o $(DYNAMICLIB) $(OBJECTS) $(LDPATH) $(LDFLAGS)

