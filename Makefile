CXX = g++
CXXFLAGS = -std=c++0x -c -g -O3
LD = g++
LDFLAGS = -std=c++0x 
EXENAME = Wicked-Cache

all : Wicked-Cache

Wicked-Cache : main.o cache.o
	$(LD) main.o cache.o -o Wicked-Cache

main.o : main.cpp cache.h
	$(CXX) $(CXXFLAGS) main.cpp

cache.o : cache.cpp cache.h
	$(CXX) $(CXXFLAGS) cache.cpp

clean :
	-rm -f *.o $(EXENAME)
