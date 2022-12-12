#pragma once

#ifndef NODE_H
#define NODE_H

#include "Edge.h"

/*
    Node class used to represent locations on a map.
    PUBLIC VARIABLEs:
        _idx: Index of node
        _x: X-Coordinate of node
        _y: Y-Coordinate of node
        _edges: Vector list of connecting edges to the node
*/
class Node {
    public:

        //Default constructor
        Node();
        
        //Overloaded constructor
        Node(unsigned idx, double latitude, double longitude, std::vector<Edge> edges); // Assignment

        //Copy constructor
        Node(const Node & other); // Copy

        //Destructor
        ~Node(); // Destructor

        unsigned _idx;
        double _x, _y;
        std::vector<Edge> _edges;
};

#endif