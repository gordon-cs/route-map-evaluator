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

Province::Province(std::istream & source) {
  // Read first line of input
  source >> _numberOfTowns >> _numberOfRoads;  
  _towns = new Town[_numberOfTowns];
  std::map<std::string, int> townMap; // maps town names to their indexes in _towns

  // Read town names
  for (int i = 0; i < _numberOfTowns; i++) {
    source >> _towns[i]._name; 
    townMap[_towns[i]._name] = i;
  }   

  // Read roads
  for (int i = 0; i < _numberOfRoads; i++) {
    string tail, head;
    char bridgeFlag;
    double length;
    source >> tail >> head >> bridgeFlag >> length;
    bool isBridge = (bridgeFlag == 'B');
    _towns[townMap.at(tail)]._roads.push_back(Road(townMap.at(head), townMap.at(tail), isBridge, length));
    _towns[townMap.at(head)]._roads.push_back(Road(townMap.at(tail), townMap.at(head), isBridge, length));
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
  


