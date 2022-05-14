/*
* CPS 222 - Project 5
* Authors: Elijah Opoku-Nyarko and Jake Colbert
*/

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <queue>

class Province {
  public:

	/**
  * Constructor
  * @param source Input data for province
  *
  * The constructor handles input data and creates a new province graph
  * with town and road data
  */
	Province(std::istream & source);

  /**
  * Print towns and roads in province in breadth-first search order
  * @param output Stream to print data to
  */
  void printAll(int start, std::ostream & output);

  /**
   * Print the shortest path conections from the capital of a province
   * to all other towns
   *
   * @param output Stream to print data to
   */
  void printShortestPath(std::ostream & output) const;

  /**
  * Find shortest path from one town to another
  */
  void findShortestPath();

  /**
   * Create a minimum cost spanning tree of a province
   * to calculate ideal
   *
   * @param output Stream to print data to
   */
  void minSpan(std::ostream & output) const;

  /**
   * Remove bridges from the graph to evaluate
   * which towns would become isolated by a storm
   *
   * @param output Stream to print data to
   */
  void removeBridges(std::ostream & output) const;

  /**
   * Find the articulation points of a graph
   *
   * @param output Stream to print data to
   */
  void articulationPoints(std::ostream & output);

  ~Province() {}

private:

  //RT Indentation was wrong because a tab was used, here and for
  // comment below (several places);
  // also there should be a blank line between methods.

  //RT Need comment here
  int smallest(double dist [], std::list <int> toVisit, int numTowns) const;

  //RT Need comment here
  //RT Line was too long:
  // https://google.github.io/styleguide/cppguide.html#Line_Length
  void dfs(int v, bool visited[], int low[], int tin[], int & timer,
           std::vector<int> & ap, int p);

  /**
   * Conduct a breadth-first traversal on the province, ignoring bridges
   * @param start Index of town to start traversal at
   * @return - List of indices of towns in order of traversal
   */
  std::vector<int> bfs(int start) const;

  /**
  * Road
  * Contains index of originating town, whether or not is bridge,
  * and length
  */
  class Road {
    public:

    /*
    * Constructor
    * @param head Index in vertex array of originating town
    * @param isBridge Whether or not the road is a bridge
    * @param length Length of the road in miles
    */
    Road(int head, int tail, char isBridge, double length)
      : _head(head), _tail(tail), _isBridge(isBridge), _length(length)
    {}

  	int _head; // Index of originating town in vertex array
    int _tail;
    char _isBridge;
    double _length;

    bool operator < (Road road2) const;
  };

  /**
  * Town
  * Contains name and a list of roads that connect to it
  */
  class Town {
    public: // consider making some of these private (RoadList)
      std::string _name;
      typedef std::list <Road> RoadList;
      RoadList _roads;
  };

  //RT Class data needs comments
  int _numberOfTowns;
	int _numberOfRoads;
  //RT Why an array of towns but a vector of roads?
  // Seems like they are used similarly and it would be simpler
  // for them to be the same.
	Town *_towns;
  std::vector<Road> _roads;
};
