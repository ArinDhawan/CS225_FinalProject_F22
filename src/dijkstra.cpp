#include "dijkstra.h"


Dijkstra::Dijkstra() {
    // default
}

// takes in an ordered vector of nodes
Dijkstra::Dijkstra(vector<Node> dataset, unsigned start_index) {
    // initialize distances to some impossible distance (-1)

    for (unsigned i = 0; i < dataset.size(); i++) {
        // 'start_idx' is the user input, which may not be the actual index
        //!use helper function here
        if (dataset[i]._idx == start_index) {
            start_ = i;
        }

        pair<unsigned, unsigned> p;
        p.first = dataset[i]._idx;
        p.second = 0;


        path.push_back(p);  // insert all nodes, and make their 'previus' node invalid
        
    }
    
    // initialize distances to max and visited as false
    distances_     = vector<double>(dataset.size(), UINT_MAX);

    nodes_visited_ = vector<bool>(dataset.size(), false);

    dataset_ = dataset; // copy over the dataset
    path[start_].second = path[start_].first;    // the 'start' node has no prev. just set to self

    distances_[start_] = 0;
    
    add_node_to_visited(dataset_[start_]._idx);

}

Dijkstra::~Dijkstra() {

}

void Dijkstra::solve() {
    
    // continue until every edge has been visited
    // once an edge is visited, erase it using edges_.erase (edges_.begin()+index);
    while (edges_.size() != 0) {

        // find the smallest edge...O(n) runtime...not the best
        unsigned shortest_dist = UINT_MAX;  // vals will always be smaller
        unsigned shortest_idx = 0;
        
        //!replace with quicksort function
        for (unsigned i = 0; i < edges_.size(); i++) {
            if (edges_[i]._weight < shortest_dist) {
                shortest_dist = edges_[i]._weight;
                shortest_idx = i;
            }
        }

        // start node should already be part of visited
        // end node may or may not be added
        unsigned start_node_idx = get_node_idx(edges_[shortest_idx]._start_node_idx);
        unsigned end_node_idx   = get_node_idx(edges_[shortest_idx]._end_node_idx);

        double end_dist = distances_[start_node_idx] + edges_[shortest_idx]._weight;

        // if the end node HAS NOT been visited, then visit it & add its edges
        if (!nodes_visited_[end_node_idx]) {
            add_node_to_visited(end_node_idx);
        }
        // See if the distance needs to be changed (regardless of visited status)
        if (end_dist < distances_[end_node_idx]) {
            // if smaller, replace the distance
            distances_[end_node_idx] = end_dist;

            // update the previous node
            path[end_node_idx].second = start_node_idx;

            // remove that edge from the edges_ list
        }
        
        edges_.erase (edges_.begin() + shortest_idx);


    }
    
    print_path();

    return;
}

/* once we switch to a new node, we add it (and all its edges) to the 
*  visited & edges_available vectors
*/
void Dijkstra::add_node_to_visited(unsigned node_index) {
    cout << "nodes_visited in add_node_to_visited" << endl;
    
    cout << "input node for nodes_visited: " << node_index << endl;
    unsigned idx = get_node_idx(node_index);
    cout << "index for nodes_visited: " << idx << endl;

    nodes_visited_[idx] = true;    // add current node to the visited list

    for (unsigned i = 0; i < dataset_[idx]._edges.size(); i++) {
        edges_.push_back(dataset_[idx]._edges[i]);
    }

}

unsigned Dijkstra::get_node_idx(unsigned node_index) {


    for (unsigned i = 0; i < dataset_.size(); i++) {
        if (dataset_[i]._idx == node_index) {
            return i;
        }
    }

    return node_index;
}


void Dijkstra::print_path() {
    for (unsigned i = 0; i < path.size(); i++) {
        cout << "Node      : " << path[i].first  << endl;
        cout << "Previous  : " << path[i].second << endl;
        cout << "Distance  : " << distances_[i]  << endl;
        cout << "----------------------" << endl;
    }
}