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

int Province::smallest(double dist[], std::list <int> toVisit,
  int numTowns) const {
  int smallest = toVisit.front();

  if (toVisit.size() > 1) {
    for (int i = 0; i < numTowns; i++) {
      if (dist[i] < dist[smallest]) {
        bool found = (std::find(toVisit.begin(), toVisit.end(), i)
                      != toVisit.end());
        if (found) {
          smallest = i;
        }
      }
    }
  }
    return smallest;
}

/**
* Print the shortest route from the capital of the
* province to each of the other towns
*/
void Province::printShortestPath(std::ostream & output) const {

    // if there is only one town only one town
    if (_numberOfTowns == 1) {
        output << "There is only one town, so the provincial "
               << "officials have no need of efficient routes!";
        return;
    }

    output << "The shortest routes from " + _towns[0]._name;
    output << " are:" << std::endl << std::endl;

    // keeps track of the index of the predecessor to each
    // town(vertex) n on the shortest path to n
    int prev[_numberOfTowns];

    // queue to keep track of which town(vertex) to visit next
    list <int> toVisit;

    // keeps track of the distance from the capital to each town
    // following the shortest path
    double dist[_numberOfTowns];


    // set defaults for dist, prev, and add all vertices to toVisit
    for (int i = 0; i < _numberOfTowns; i++) {
        dist[i] = DBL_MAX;
        toVisit.push_back(i);
    }

    // distance from the capital to the capital is zero
    dist[0] = 0.0;

    while (!toVisit.empty()) {
        int smallestIndex = smallest(dist, toVisit, _numberOfTowns);

        toVisit.remove(smallestIndex);

        // Add current vertex's neighbors to the queue
        for (Town::RoadList::iterator neighbor =
            _towns[smallestIndex]._roads.begin();
            neighbor != _towns[smallestIndex]._roads.end(); neighbor++) {
            // new distance needed for testing
            double newDist = dist[smallestIndex] + neighbor->_length;

            // if new dist is smaller, replace the old one, and
            // update the corresponding entry in prev
            if (newDist < dist[neighbor->_head]) {
                dist[neighbor->_head] = newDist;
                prev[neighbor->_head] = smallestIndex;
            }
        }
    }
}


