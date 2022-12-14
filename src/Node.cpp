#include "Node.h"

//Default constructor
Node::Node(){
  _idx = -1;
  _x = -1;
  _y = -1;
  _edges = std::vector<Edge>();
}

//Overloaded constructor
Node::Node(unsigned idx, double latitude, double longitude, std::vector<Edge> edges){
            _idx = idx;
            _x = latitude;
            _y = longitude;
            _edges = edges;
        }

//Copy constructor
Node::Node(const Node & other){
  _idx = other._idx;
  _x = other._x;
  _y = other._y;
  _edges = other._edges;
}

//Destructor
Node::~Node() {
  _edges.clear();
}

