CXX = g++
CXXFLAGS = -Wall

all: main tests

main: graph.cpp main.cpp
	$(CXX) $(CXXFLAGS) graph.cpp main.cpp -o main

tests: test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o tests

clean:
	rm -f main tests *.txt

test_small: tests main
	./tests
	./main graph_small.txt cycle_small.txt 10

test_medium: main
	./main graph_medium.txt cycle_medium.txt 20

test_large: main
	./main graph_large.txt cycle_large.txt 30