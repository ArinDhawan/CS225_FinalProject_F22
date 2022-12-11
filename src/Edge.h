#pragma once

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <utility>
#include <string>
#include <cmath>


/* taken from main*/
/* Edge Class */
class Edge {
    public:
        Edge(unsigned idx, unsigned start_node_idx, unsigned end_node_idx, double weight); // Assignment

        Edge(const Edge & other); // Copy

        ~Edge(); // Destructor

        unsigned _idx;
        unsigned _start_node_idx, _end_node_idx;
        double _weight;
};


#endif