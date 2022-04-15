# Author: Elijah Opoku-Nyarko and Jake Colbert

# default target
all: project5

# compile the code into an executable called 'project1' using C++ 2011
project5:	project5.cc province.h
	g++ -std=c++11 -o project5 project5.cc

# test the code against an expected output file
# this test should grow into a spaceship and end with blinkers
test-nowhere:
	./project5 < test-files/t01-nowhere.in > tests/project4.out
	diff test-files/project4.out test-files/t01-nowhere.out > test.diff
	wc -l test.diff
