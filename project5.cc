/*
* @file: project5.cc
*
*@brief:
* Main program for CPS222 project 5 - test driver to read in a graph
* from standard input and test the read graph
*
* @Authors: Elijah Opoku-Nyarko & Jake Colbert
*/

#include <iostream>
#include <string>
#include "./province.h"

using namespace std;

/*
* check if we are at the end of the file
*/
bool eof() {
  char c;
  cin >> c;
  // if the fie is ended, return true
  if (cin.eof()) {
    return true;
  } else {
    // if the file contains more data, return the previously gotten
    // data to cin
    cin.unget();
    return false;
  }
}

int main(int argc, char *argv[]) {
  // Repeatedly read input from standard input
  while (!eof()) {
    // create a new graph for each loop, which will read all of the
    // corresponding data per graph
    Province theProvince(cin);

    cout << endl;
    cout << "------------------------------------------------" << endl;
    cout << "---------------- New DataSet: ------------------" << endl;
    cout << "------------------------------------------------" << endl;
    cout << endl;

    theProvince.printAll(0, cout);

      
  }
}
