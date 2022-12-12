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

/*
    Edge class used to represent connections between nodes.
    PUBLIC VARIABLEs:
        _idx: Index of edge
        _start_node_idx: Starting node of edge
        _end_node_idx: Ending node of edge
*/
class Edge {
    public:

        //Default constructor
        Edge();

        //Overloaded constructor
        Edge(unsigned idx, unsigned start_node_idx, unsigned end_node_idx, double weight); // Assignment

        //Copy constructor
        Edge(const Edge & other);

        //Destructor
        ~Edge();

        unsigned _idx;
        unsigned _start_node_idx, _end_node_idx;
        double _weight;
};

#endif