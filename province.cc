/*
* Implentation of Province.h
* Authors: Elijah Opoku-Nyarko and Jake Colbert
*/

#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <cfloat>
#include <array>

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
    _roads.push_back(Road(townMap.at(head), townMap.at(tail), isBridge, length));
    _towns[townMap.at(tail)]._roads.push_back(
            Road(townMap.at(head), townMap.at(tail), isBridge, length));
    _towns[townMap.at(head)]._roads.push_back(
            Road(townMap.at(tail), townMap.at(head), isBridge, length));
  }   
}

void Province::printAll(int start, std::ostream & output) {
  // keep track of whether a town(vertex) has been scheduled to be visited
  bool scheduled[_numberOfTowns];
  memset(scheduled, 0, sizeof scheduled); // initialize to 0/false

  // Keep track of which towns have been visited
  queue <int> toVisit; // use queue to keep track of which town to visit next
  toVisit.push(start);
  scheduled[start] = true;
  output << "The input data is:" << endl << endl;

  // Visit every town in the queue
  while (!toVisit.empty()) {
    int current = toVisit.front();
    toVisit.pop();

    output << _towns[current]._name << endl;

    // Add current town's(vertex's) unscheduled neighbors to the queue
    for (Town::RoadList::iterator neighbor = _towns[current]._roads.begin();
      neighbor != _towns[current]._roads.end(); neighbor++) {
        std::string neighborName = _towns[neighbor->_head]._name;
        output << "        " << neighborName << " " << neighbor->_length << " mi";

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
  output << endl;
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

void Province::printShortestPath(std::ostream & output) const {

  // if there is only one town only one town
  if (_numberOfTowns == 1) {
      output << "There is only one town, so the provincial "
             << "officials have no need of efficient routes!";
      return;
  }

  output << "The shortest paths from " + _towns[0]._name;
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

  // print out the data for each non capital town
  for (int i = 1; i < _numberOfTowns; i++) {
    output << "    " << "The shortest path from " + _towns[0]._name;
    output << " to " + _towns[i]._name + " is " << dist[i];
    output << " mi:" << std::endl;

    // stack to hold the path to the town at index i
    std::stack <int> predecessors;

    // add town at i to stack
    int predecessor = i;
    predecessors.push(i);

    // follow the links in prev until we get to the capital,
    // adding each town to the predecessor stack
    while (predecessor != 0) {
      predecessor = prev[predecessor];
      predecessors.push(predecessor);
    }
    // print out the names for each entry in the stack
    while (!predecessors.empty()) {
        output << "        " << _towns[predecessors.top()]._name;
        output << std::endl;
        predecessors.pop();
    }
  }
  cout << endl;  
}

bool Province::Road::operator < (Road road2) const {
  return this->_length < road2._length;
}

void Province::minSpan(std::ostream & output) const {
  // if only one town
  if (_numberOfTowns == 1) {
    output << "There is only one town, so the province "
           << "does not need to upgrade any roads!";
      return;
  }
    
  list<Road> roads;
  vector<Road> minSpanTree;
  vector<int> higher;
    
  // Initialize a numComponent value for each town to 0
  int numComponent[_numberOfTowns];
  for (int i = 0; i < _numberOfTowns; i++) {
    numComponent[i] = 0;
  }
    
  // Add all roads to list of roads
  for (int i = 0; i < _numberOfRoads; i++) {
    roads.push_back(_roads[i]);
  }

  // Sort list of roads by length
  roads.sort();
  int compNum = 0;  // Used to determine if edge forms a cycle

  while (minSpanTree.size() < _numberOfTowns - 1) {
    Road minRoad = roads.front();
    roads.pop_front();

    // Both towns have component number 0
    if (numComponent[minRoad._head] == 0 &&
      numComponent[minRoad._tail] == 0) {
      minSpanTree.push_back(minRoad);
      compNum++;
      numComponent[minRoad._head] = compNum;
      numComponent[minRoad._tail] = compNum;

    // Only one town has component number 0
    } else if (numComponent[minRoad._head] == 0) {
      minSpanTree.push_back(minRoad);
      numComponent[minRoad._head] = numComponent[minRoad._tail];

    // Other town has component number 0
    } else if (numComponent[minRoad._tail] == 0) {
      minSpanTree.push_back(minRoad);
      numComponent[minRoad._tail] = numComponent[minRoad._head];

    // If component number of one town is less than other town
    } else if (numComponent[minRoad._head] <
      numComponent[minRoad._tail]) {
      minSpanTree.push_back(minRoad);
      higher.push_back(minRoad._tail);

      // Set all higher road components to value of lower
      for (int i = 0; i < higher.size(); i++) {
        higher[i] = numComponent[minRoad._head];
      }

    // If component number of other town is less than other town
    } else if (numComponent[minRoad._head] >
                numComponent[minRoad._tail]) {
      minSpanTree.push_back(minRoad);
      higher.push_back(minRoad._head);

      // Set all higher road components to value of lower
      for (int i = 0; i < higher.size(); i++) {
        higher[i] = numComponent[minRoad._tail];
      }
    } 
  }
  output << "The road upgrading goal can be achieved at minimal cost by upgrading:";
  output << std::endl;

  // Print names of towns in minimum spanning tree of province
  for (int i = 0; i < minSpanTree.size(); i++) {
    output << "    ";
    output << _towns[minSpanTree[i]._head]._name;
    output << " to ";
    output << _towns[minSpanTree[i]._tail]._name << std::endl;
  }      
  output << endl;
}
      
std::vector<int> Province::bfs(int start) const {
  // Initialize list of towns scheduled to visit
  bool scheduled[_numberOfTowns];
  memset(scheduled, 0, sizeof scheduled); // initialize to 0/false

  // Initialize list of towns to visit with starting town
  std::queue<int> toVisit;
  toVisit.push(start);
  scheduled[start] = true;
  std::vector<int> results;

  // While all towns have not been visited
  while (!toVisit.empty()) {
    // Remove current town from queue and add to results
    int current = toVisit.front();
    toVisit.pop();
    results.push_back(current);

    // Iterate over neighbors to current town
    for (Town::RoadList::iterator neighbor =
        _towns[current]._roads.begin();
      neighbor != _towns[current]._roads.end();
      neighbor ++) {

      // If neighbor is not bridge and is not scheduled,
      // add to results and schedule
      if (!neighbor->_isBridge && !scheduled[neighbor->_head]) {
        toVisit.push(neighbor->_head);
        scheduled[neighbor->_head] = true;
      }
    }
  }
  return results;
}

/**
 * Remove bridges and print the list of towns that remain connected
 */
void Province::removeBridges(ostream &output) const {
  // Look for a bridge
  bool hasBridge = false;
  for ( int roadNum = 0; roadNum < _roads.size(); roadNum++) {
    if (_roads[roadNum]._isBridge) {
      hasBridge = true;
      break;
    }
  }

  // Mark all towns as unvisited
  list<int> toVisit;
  for (int i = 0; i < _numberOfTowns; i++) {
    toVisit.push_back(i);
  }
  output << "Connected components in event of a major storm are:";
  output << endl;

  while (!toVisit.empty()) {
    // Mark current town as visited
    int curr = toVisit.back();
    toVisit.pop_back();

    // Run BFS from current town
    vector<int> bfsResult = bfs(curr);

    // Mark all town in BFS result as visited
    for (int i = 0; i < bfsResult.size(); i++) {
      toVisit.remove(bfsResult[i]);
    }

    output << "   ";
    output << "If all bridges fail, the following towns would form ";
    output << "an isolated group:" << endl;

    // Print names of all towns in connected component
    for (int i = 0; i < bfsResult.size(); i++) {
      output << "        ";
      output << _towns[bfsResult[i]]._name << endl;
    }
    output << endl;
  }
}

void Province::dfs(int v, 
                   bool visited[], 
                   int low[], 
                   int tin[], 
                   int & timer, 
                   std::vector<int> & ap, 
                   int p = -1) 
{
  visited[v] = true;
  tin[v] = low[v] = timer++;
  int children=0;
  for (Road to : _towns[v]._roads) {
    if (to._tail == p) continue;
    if (visited[to._head]) {
      low[v] = min(low[v], tin[to._head]);
    } else {
      dfs(to._head, visited, low, tin, timer, ap, v);
      low[v] = min(low[v], low[to._head]);
      if (low[to._head] >= tin[v] && p!=-1) {
        ap.push_back(v);
      }  
      ++children;
    }
  }
  if (p == -1 && children > 1) {
    ap.push_back(v);
  }
}

void Province::articulationPoints(std::ostream & output) {
  std::vector<int> ap;
  bool visited[_numberOfTowns];  memset(visited, 0, sizeof visited);
  int tin[_numberOfTowns]; memset(tin, 0, sizeof tin);
  int low[_numberOfTowns]; memset(low, 0, sizeof low);
  int timer = 0;
  for (int i = 0; i < _numberOfTowns; ++i) {
    if (!visited[i]) {
      dfs(i, visited, low, tin, timer, ap);
    }  
  }
  output << "Destruction of any of the following would result in the province becoming";
  output << "\ndisconnected:" << endl;
  
  int apCount = 0;
  for (int i : ap) {
    output << "    " << _towns[i]._name << endl;
    apCount++;  
  }

  if (apCount == 0) { output << "    (None)" << endl; }

  output << endl;
}