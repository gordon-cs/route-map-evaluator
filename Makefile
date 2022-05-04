# Author: Elijah Opoku-Nyarko and Jake Colbert

# define colors
ifneq (,$(findstring xterm,${TERM}))
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	RESET := $(shell tput -Txterm sgr0)
else
	RED          := ""
	GREEN        := ""
	RESET        := ""
endif

# default target
all: project5

# compile the code into an executable called 'project1' using C++ 2011
project5:	project5.cc province.cc province.h
	g++ -std=c++11 -o project5 project5.cc province.cc

# test all the code
test-all:	project5 test-nowhere test-one-road test-simple test-local test-combo
	@echo ""
	@echo "$(GREEN)Passed all tests!$(RESET)"
	@echo ""

test:	project5
	./project5 < test-data/t0502-combo.in > test-data/project5.out
	diff test-data/project5.out test-data/shortest.out > test.diff

# test the code against an expected output file
test-nowhere:	project5
	@echo ""
	@echo "$(RED)--- Nowhere Test ---$(RESET)"
	@echo ""
	./project5 < test-data/t01-nowhere.in > test-data/project5.out
	diff test-data/project5.out test-data/t01-nowhere.out > test.diff
	@echo "$(GREEN)Passed!$(RESET)"

# test the code against an expected output file
test-one-road:	project5
	@echo ""
	@echo "$(RED)--- One Road Test ---$(RESET)"
	@echo ""
	./project5 < test-data/t02-one-road.in > test-data/project5.out
	diff test-data/project5.out test-data/t02-one-road.out > test.diff
	@echo "$(GREEN)Passed!$(RESET)"

# test the code against an expected output file
test-simple:	project5
	@echo ""
	@echo "$(RED)--- Simple Test ---$(RESET)"
	@echo ""
	./project5 < test-data/t03-simple.in > test-data/project5.out
	diff test-data/project5.out test-data/t03-simple.out > test.diff
	@echo "$(GREEN)Passed!$(RESET)"

# test the code against an expected output file
test-local:	project5
	@echo ""
	@echo "$(RED)--- Local Test ---$(RESET)"
	@echo ""
	./project5 < test-data/t08-local.in > test-data/project5.out
	diff test-data/project5.out test-data/t08-local.out > test.diff
	@echo "$(GREEN)Passed!$(RESET)"

# test the code against an expected output file
test-combo:	project5
	@echo ""
	@echo "$(RED)--- Combo Test ---$(RESET)"
	@echo ""
	./project5 < test-data/t0502-combo.in > test-data/project5.out
	diff test-data/project5.out test-data/t0502-combo.out > test.diff
	@echo "$(GREEN)Passed!$(RESET)"