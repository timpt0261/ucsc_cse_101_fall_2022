CXX = g++
CXXFLAGS = -Wall 

OBJECTS = avl.o treewrapper.o

treewrapper: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o treewrapper avl.o treewrapper.o

avl.o: avl.cpp avl.h
	$(CXX) -g $(CXXFLAGS) -c avl.cpp
	
treewrapper.o: avl.cpp avl.h treewrapper.cpp
	$(CXX) -g $(CXXFLAGS) -c treewrapper.cpp

clean: 
	rm -f *.o
	rm treewrapper

