#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Node.h"

#include <climits>
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

using namespace std;

class Dijkstra {
    public:
        Dijkstra();

        //!add endpiont
        Dijkstra(vector<Node> dataset, unsigned start_index);

        ~Dijkstra();


    private:
        void solve();
        void add_node_to_visited(unsigned node_index);
        unsigned get_node_idx(unsigned node_index);

        void print_path();


        vector<Node> dataset_;

        // dijkstra will return a path. We do this by storing the nodes
        // with the index of the 'previous closest node'.
        // when we walk back, we can get the entire path
        // pair<index, previous_index>
        vector<pair<unsigned, unsigned>> path;


        // this goes by the SHORTEST EDGE TO THE 'visited' LIST
        // hence why we have an edges vector, which keeps track of all the 
        // edges we can currently traverse
        vector<bool> nodes_visited_;   // keeping track of all the nodes we've been to (as a base)
        vector<Edge> edges_;           // when we add a node to the 'visited' list, we add all its edges
        vector<unsigned> distances_;

        // this is the USER INPUT. we need to handle actual vector index here
        unsigned start_;
        
};

#endif