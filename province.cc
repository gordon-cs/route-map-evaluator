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
    _towns[townMap.at(tail)]._roads.push_back(Road(townMap.at(head), townMap.at(tail), isBridge, length));
    _towns[townMap.at(head)]._roads.push_back(Road(townMap.at(tail), townMap.at(head), isBridge, length));
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

/**
 * < operator used to compare two roads
 * @param road2 A road
 * @return True if road1 is shorter in length than road 2
 */
bool Province::Road::operator < (Road road2) const {
  return this->_length < road2._length;
}

/**
 * Find minimum cost spanning tree of the province
 */
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
  for (int i = 0; i < _numberOfTowns; i ++) {
    scheduled[i] = false;
  }

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

void Province::APUtil(int u, bool visited[],
            int disc[], int low[], int& time, int parent,
            bool isAP[]) const {
  // Count of children in DFS Tree
  int children = 0;

  // Mark the current node as visited
  visited[u] = true;

  // Initialize discovery time and low value
  disc[u] = low[u] = ++time;

  // Go through all vertices adjacent to this
  for (int v = 0; v < _numberOfTowns; v++) {
    // If v is not visited yet, then make it a child of u
    // in DFS tree and recur for it
    if (!visited[v]) {
      children++;
      APUtil(v, visited, disc, low, time, u, isAP);

      // Check if the subtree rooted with v has
      // a connection to one of the ancestors of u
      low[u] = min(low[u], low[v]);

      // If u is not root and low value of one of
      // its child is more than discovery value of u.
      if (parent != -1 && low[v] >= disc[u]) {
        isAP[u] = true;
      }    
    } else if (v != parent) {
      low[u] = min(low[u], disc[v]);
    }    
  }

  // If u is root of DFS tree and has two or more children.
  if (parent == -1 && children > 1) {
      isAP[u] = true; 
  }    
}
 
void Province::articulationPoints(std::ostream & output) const
{  
  int disc[_numberOfTowns];
  memset(disc, 0, sizeof disc);
  int low[_numberOfTowns];
  bool visited[_numberOfTowns];
  memset(visited, false, sizeof visited);
  bool isAP[_numberOfTowns];
  memset(isAP, false, sizeof isAP);
  int time = 0, par = -1;

  // Adding this loop so that the
  // code works even if we are given
  // disconnected graph
  for (int u = 0; u < _numberOfTowns; u++) {
    if (!visited[u]) {
      APUtil(u, visited, disc, low, time, par, isAP);
    }
  }    
  output << "Destruction of any of the following would result in the province becoming" << endl << "disconnected:" << endl;
  int count = 0;

  // Printing the APs
  for (int u = 0; u < _numberOfTowns; u++) {
    if (isAP[u] == true) {
      output << "    " << _towns[u]._name << endl;
      count++;
    }
  }  
  if (count == 0) {
    output << "    (None)" << endl;
  }
  output << endl;

  for (bool i : isAP) {
    cerr << i << endl;
  }
}