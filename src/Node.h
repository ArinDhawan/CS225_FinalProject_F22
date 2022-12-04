#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#pragma once


class Node {
    public:
        Node(unsigned idx, double latitude, double longitude, Edge * edge); // Assignment

        Node(const Node & other); // Copy

        ~Node(); // Destructor

        unsigned _idx;
        double _x, _y;
        Edge * _edge;

};

#endif