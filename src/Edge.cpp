#include "Edge.h"

//Default constructor
Edge::Edge(){
  _idx = -1;
  _start_node_idx = -1;
  _end_node_idx = -1;
  _weight = 0;
}

//Overloaded constructor
Edge::Edge(unsigned idx, unsigned start_node_idx, unsigned end_node_idx, double weight){
  _idx = idx;
  _start_node_idx = start_node_idx;
  _end_node_idx = end_node_idx;
  _weight = weight;
}

//Copy constructor
Edge::Edge(const Edge & other){
  _idx = other._idx;
  _start_node_idx = other._start_node_idx;
  _end_node_idx = other._end_node_idx;
  _weight = other._weight;
}

//Destructor
Edge::~Edge(){
  /* nothing */
}


