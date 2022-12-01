CXX = g++
CXXFLAGS = -Wall -Wextra

OBJECTS =  sixdegrees.o

sixdegrees: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees  sixdegrees.o

sixdegrees.o: sixdegrees.cpp
	$(CXX) -g $(CXXFLAGS) -c sixdegrees.cpp

clean: 
	rm -f *.o
	rm sixdegrees