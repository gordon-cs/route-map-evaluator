# cps222p5-test-data

This repo provides sample input and output files for testing your
Project 5 code.  Much more test data is needed to ensure your
code works. Remember: **if you haven't tested it, it doesn't work.**

* .in: sample input
* .out: expected output for matching input.  Please match the format of each line exactly, by comparing your output to this with the "diff" command.  Try to make the output line order match, too.  But if you are confident your code is producing correct output in a different valid order, that is acceptable.

There is also a .jpg image of a diagram of some input.

Elijah: 

To run a test from the make file, execute `make <test name>` where test name is the target name of the test. At the moment you read this, the only availible test target in the makefile is a test named "test-requirement1". To run this test target, execute `make test-requirement1` in the terminal. This will run the code with an imput file and compares the output of the test with the expected output using the diff unix command. 