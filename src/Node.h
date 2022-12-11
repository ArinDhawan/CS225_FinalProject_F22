#ifndef NODE_H
#define NODE_H

#include "Edge.h"

#pragma once


class Node {
    public:
        Node();
        
        Node(unsigned idx, double latitude, double longitude, std::vector<Edge> edges); // Assignment

        Node(const Node & other); // Copy

        ~Node(); // Destructor

        unsigned _idx;
        double _x, _y;
        std::vector<Edge> _edges;
};

#endif