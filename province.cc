/*
* Implentation of Province.h
* Authors: Elijah Opoku-Nyarko and Jake Colbert
*/

#include "./province.h"
#include <algorithm>
#include <string>
#include <stack>
#include <cfloat>

using namespace std;

/*
* Constructor
* @param source File containing province:
*               1. One line: number of towns (n), number of roads (p)
*                  as integers
*               2. n lines: names of towns, all uppercase
*               3. p lines: roads, defined as names of towns they
*                  connect, bridge/not bridge, and length in miles
*                  ex: BEVERLY DANVERS N 2.9 (connects Beverly and
*                      Danvers, not a bridge, 2.9 miles long)
*/

Province::Province(std::istream & source) {
  // Read first line of input
  source >> _numberOfTowns >> _numberOfRoads;  
  _towns = new Town[_numberOfTowns];
  std::map<std::string, int> townMap; // maps town names to their indexes in _towns

  // Read town names
  for (int i = 0; i < _numberOfTowns; i++) {
    source >> _towns[i]._name; // This needs to be converted to vector, im not sure how exactly
    townMap[_towns[i]._name] = i;
  }   

  for (int i = 0; i < _numberOfRoads; i++) {
    string head, tail;
    char bridge;
    float distance; 
    source >> head >> tail >> bridge >> distance;
    // add a road to the _roads array that belongs to the town at the index map.at(head) returns
    _towns[townMap.at(head)]._roads.push_back(Road(townMap.at(head), townMap.at(tail), bridge, distance));
  }   
}

void Province::printAll(std::ostream & output) {
  output << "The input data is:" << endl << endl;
  for (int i = 0; i < sizeof(_towns)/sizeof(_towns[0]); i++) {
    output << _towns[i]._name << endl;
    for (Road road : _towns[i]._roads) {
      output << "\t" << road._tail << " " << road._length << " mi";
      if (road._isBridge == 'B' || 'b') {
        output << " via bridge" << endl;
      } else {
        output << endl;
      }
    }
  }
}