/*
* CPS 222 - Project 5
* Authors: Elijah Opoku-Nyarko and Jake Colbert
*/

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <queue>


// re-evaluate security of these classes


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
     * @param output Stream to print data to
     */
    void printAll(int start, std::ostream & output);
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
    ~Province() {}

private:

    int smallest(double dist [], std::list <int> toVisit, int numTowns) const;
    std::vector<int> bfs(int start) const;
    void dfsAux(int current, std::vector<int> & dfsTowns, bool visited []) const;

    /**
     * Road
     * Contains index of originating town, whether or not is bridge,
     * and length
     */
    class Road
    {
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
    class Town
    {
    public: // consider making some of these private (RoadList)
        std::string _name;
        typedef std::list <Road> RoadList;
        RoadList _roads;
    };

    int _numberOfTowns;
    int _numberOfRoads;
    Town *_towns;
    std::vector<Road> _roads;
};
