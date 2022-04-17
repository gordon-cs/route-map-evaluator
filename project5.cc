/**
 * @file project5.cc
 * @author Elijah Opoku-Nyarko and Jake Colbert
 * @brief 
 * @version 0.1
 * @date 2022-04-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * Project 5 main file
 */

#include <iostream>
#include <string>
#include <fstream>

#include "province.h"

using namespace std;

int main() {
  while(!cin.eof()) {
    Province theProvince(cin);
    theProvince.printAll(cout);
  }
}

