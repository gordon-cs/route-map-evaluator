# Author: Elijah Opoku-Nyarko and Jake Colbert

# default target
all: project5

# compile the code into an executable called 'project1' using C++ 2011
project5:	project5.cc province.cc province.h
	g++ -std=c++11 -o project5 project5.cc province.cc

# test the code against an expected output file
# this test should grow into a spaceship and end with blinkers
test-requirement1:	project5
	./project5 < test-data/requirement1.in > test-data/project5.out
	diff test-data/project5.out test-data/requirement1.out
