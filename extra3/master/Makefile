CCX = g++
CXXFLAGS = -std=c++11 -Wall -Wdeprecated -pedantic -DMEMTRACE -g 

HEADERS := $(wildcard *.h) $(wildcard *.hpp)
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)

main: $(OBJECTS)
	$(CCX) $^ -g -o $@ -ldl
	
%.o: %.c $(HEADERS)
	$(CCX) $(CXXFLAGS) -c $<
	
clean:
	rm -rf $(OBJECTS) main
