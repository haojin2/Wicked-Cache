CXX = g++
CXXFLAGS = -std=c++0x -c -g -O0
LD = g++
LDFLAGS = -std=c++0x
EXENAME = wicked test

wicked : main.o cache.o snoop.o memops.o protocol.o
	$(LD) $(LDFLAGS) main.o cache.o snoop.o memops.o protocol.o -o wicked

all : wicked test

test: test.o
	$(LD) test.o -o test

test.o: test.cpp mesi.h msi.h mosi.h moesi.h mesif.h
	$(CXX) $(CXXFLAGS) test.cpp

main.o : main.cpp snoop.h
	$(CXX) $(CXXFLAGS) main.cpp

snoop.o : snoop.cpp snoop.h memops.h protocol.h cache.h snoop_config.h
	$(CXX) $(CXXFLAGS) snoop.cpp

memops.o : memops.cpp memops.h 
	$(CXX) $(CXXFLAGS) memops.cpp

protocol.o : protocol.cpp protocol.h memops.h
	$(CXX) $(CXXFLAGS) protocol.cpp

cache.o : cache.cpp cache.h
	$(CXX) $(CXXFLAGS) cache.cpp

clean :
	rm -f *.o $(EXENAME)
