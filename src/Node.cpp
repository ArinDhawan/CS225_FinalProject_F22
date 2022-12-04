#include "Node.h"

Node::Node(unsigned idx, double latitude, double longitude, Edge * edge){
            _idx = idx;
            _x = latitude;
            _y = longitude;
            _edge = edge;
        }

Node::Node(const Node & other){
  _idx = other._idx;
  _x = other._x;
  _y = other._y;
  _edge = other._edge;
}

Node::~Node() {
  _edge->~Edge();
}

