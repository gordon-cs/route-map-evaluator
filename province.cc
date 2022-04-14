/*
* Implentation of Province.h
* Authors: Elijah Opoku-Nyarko and Jake Colbert
*/

#include "./province.h"
#include <algorithm>
#include <stack>
#include <cfloat>

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
Province::Province(std::istream &source) {
    // Read first line of input
    source >> _numberOfTowns >> _numberOfRoads;

    _towns = new Town[_numberOfTowns];    
    std::map<std::string, int> nameMap;

    // Read town names
    for (int i = 0; i < _numberOfTowns; i++) {
        source >> _towns[i]._name;
        nameMap[_towns[i]._name] = i;
    }