/*
* CPS 222 - Project 5
* Authors: Elijah Opoku-Nyarko and Jake Colbert
*/

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <queue>

/**
 * towns connected by roads
 */
class Province
{
public:

    /**
     * Constructor
     * @param source Input data for province
     */
    Province(std::istream & source);

    /**
     * Print towns and roads in province in breadth-first search order
     * @param start Index to start traversal at
     * @param output Stream to print data to
     */
    void printAll(int start, std::ostream & output) const;

    void printShortestPath(std::ostream & output) const;
    
    /**
     * Find shortest path from one town to another
     */
    void findShortestPath();

    void minSpan(std::ostream & output) const;

    void removeBridges(std::ostream & output) const;

    void articulationPoints(std::ostream & output) const;

    void dfs(std::vector<int> & dfsTowns) const;

    /**
     * Destructor
     */
    ~Province() { delete [] _towns; }

private:

    int smallest(double dist [], std::list <int> toVisit, int numTowns) const;
    std::vector<int> bfs(int start) const;
    void dfsAux(int current, std::vector<int> & dfsTowns, bool visited []) const;



    