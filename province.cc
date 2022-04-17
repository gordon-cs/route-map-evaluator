/*
* Implentation of Province.h
* Authors: Elijah Opoku-Nyarko and Jake Colbert
*/

#include <algorithm>
#include <string>
#include <stack>
#include <cfloat>

#include "province.h"

using namespace std;

/*f
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
    cout << "This is the name: " << &_towns[i]._name << endl;
    townMap[_towns[i]._name] = i;
  }   

  // Read roads
  for (int i = 0; i < _numberOfRoads; i++) {
        std::string tail, head;
        source >> tail >> head;
        int tailIndex = townMap[tail];  // index of the first town
        int headIndex = townMap[head];  // index of the second town

  // Get the type of road ("B" If Bridge, "N" if normal road)
  char type;
  source >> type;
  bool isBridge = (type == 'B');
  // Not sure how to Get the type if it is a normal road (ie. Not a Bridge) 

  // Length of road
  double length;
  source >> length;

  // Add a road to the road list
  Road newRoad(headIndex, tailIndex, isBridge, length);
  _roads.push_back(newRoad);

  // Add a road to two connecting towns
  _towns[tailIndex]._roads.push_back(Road(headIndex, tailIndex,
                                          isBridge, length));
  _towns[headIndex]._roads.push_back(Road(tailIndex, headIndex,
            isBridge, length));


  }   
}

// void Province::printAll(std::ostream & output) {
//   output << "The input data is:" << endl << endl;
//   cout << endl << "Size of towns: " << sizeof(&_towns)/sizeof(&_towns[0]) << endl;
//   for (int i = 0; i < sizeof(&_towns)/sizeof(&_towns[0]); i++) {
//     output << _towns[i]._name << endl;
//     for (Road _road: _towns[i]._roads) {
//       output << "\t" << road._tail << " " << road._length << " mi";
//       if (road._isBridge == 'B' || 'b') {
//         output << " via bridge" << endl;
//       } else {
//         output << endl;
//       }
//     }
//   }
// }