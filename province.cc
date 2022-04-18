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
    //cout << "This is the name: " << &_towns[i]._name << endl;
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

void Province::printAll(int start, std::ostream & output) {
  // keep track of whether a town(vertex) has been scheduled to be visited
  bool scheduled[_numberOfTowns];
  for (int i = 0; i < _numberOfTowns; i++){
    scheduled[i] = false;
  }

  // Keep track of which towns have been visited
  queue <int> toVisit; // use queue to keep track of which town to visit next
  toVisit.push(start);
  scheduled[start] = true;
  output << "The input data is :" << endl << endl;

  // Visit every town in the queue
  while (!toVisit.empty()) {
    int current = toVisit.front();
    toVisit.pop();

    output << "   ";
    output << _towns[current]._name << endl;

    // Add current town's(vertex's) unscheduled neighbors to the queue
    for (Town::RoadList::iterator neighbor = _towns[current]._roads.begin();
      neighbor != _towns[current]._roads.end(); neighbor++) {
        std::string neighborName = _towns[neighbor->_head]._name;

        output << "         ";
        output << neighborName << " " << neighbor->_length << " mi";

        // if the type is bridge, then add to output
        if (neighbor ->_isBridge) {
          output << " via bridge";
        }

        output << endl; 

        int head = neighbor ->_head;

        // If neighbour is not scheduled, add neighbor to the queue
        if (!scheduled[head]) {
          toVisit.push(head);
          scheduled[head] = true;
        }
      }
  }

  output << endl << endl;

}
  


