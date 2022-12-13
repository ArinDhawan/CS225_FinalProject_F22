#include "dijkstra.h"


Dijkstra::Dijkstra() {
    // default
}

/* Dijkstra(vector<Node> dataset, unsigned start_index)
*   Default constructor for the Dijkstra object
*   Takes in a dataset of Nodes, and a starting index
*   initializes all the vectors (as blank/0) and sets the desired starting node
*/
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


/* solve()
*   The main function of this algorithm.
*
*   Steps:
*   1. Mark current node as visited
*   2. Add all the edges from the current node to the edges_
*   3. Find the shortest edge from the edges_ vector
*   4. Follow the shortest edge and update the current node
*   5. If the distance from the previous node is shorter than that node’s current distance, then update it’s current distance. Also update it’s “previous” part 
*      in the ‘path’ vector
*   6. Repeat steps 1-4 until all edges have been visited
*/
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
    
    //print_path();

    return;
}


/* add_node_to_visited(unsigned node_index)
*   Mark the node as 'visited' so we don't loop over it again.
*   Push all this node's edges onto the 'edges_' vector
*/
void Dijkstra::add_node_to_visited(unsigned node_index) {
    //cout << "nodes_visited in add_node_to_visited" << endl;
    
    //cout << "input node for nodes_visited: " << node_index << endl;
    unsigned idx = get_node_idx(node_index);
    //cout << "index for nodes_visited: " << idx << endl;

    nodes_visited_[idx] = true;    // add current node to the visited list

    for (unsigned i = 0; i < dataset_[idx]._edges.size(); i++) {
        edges_.push_back(dataset_[idx]._edges[i]);
    }

}


/* get_node_idx(unsigned node_index)
*   The node index isn't necessarily the index in our vector (node 500 could be the 2nd index).
*   This returns the index of our desired node (with given ID) within our vectors
*/
unsigned Dijkstra::get_node_idx(unsigned node_ID) {


    for (unsigned i = 0; i < dataset_.size(); i++) {
        if (dataset_[i]._idx == node_ID) {
            return i;
        }
    }

    return -1;
}


/* print_path_()
*  Identical to print_path_file, but prints to the console
*  Prints to 'output3.txt'. 
*  Data printed:
*       - Node index
*       - This node's 'previous' node index
*       - This node's distance from start
*/
void Dijkstra::print_path() {
    for (unsigned i = 0; i < path.size(); i++) {
        cout << "Node      : " << path[i].first  << endl;
        cout << "Previous  : " << path[i].second << endl;
        cout << "Distance  : " << distances_[i]  << endl;
        cout << "----------------------" << endl;
    }

    print_path_file();
}


/* print_path_file()
*  Prints to 'output3.txt'. 
*  Data printed:
*       - Node index
*       - This node's 'previous' node index
*       - This node's distance from start
*/
void Dijkstra::print_path_file(){

    string file_name = "output3.txt";

    std::ofstream output(file_name);
    if(!output.is_open()) return;

    for (unsigned i = 0; i < path.size(); i++) {

        if (distances_[i] != UINT_MAX) {
            output << "Node      : " << path[i].first  << endl;
            output << "Previous  : " << path[i].second << endl;
            output << "Distance  : " << distances_[i]  << endl;
            output << "----------------------" << endl;
        }

    }



    output.close();
}


/* get_pair_at_node(unsigned index)
*  Returns the pair of <node_index, previous_node> 
*/
pair<unsigned, unsigned> Dijkstra::get_pair_at_node(unsigned index) {
    unsigned idx = get_node_idx(index);

    return path[idx];
}


/* get_distance_at_node(unsigned index)
*  Getter function to grab the distance of the desired node number
*/
double Dijkstra::get_distance_at_node(unsigned index) {
    unsigned idx = get_node_idx(index);
    
    return distances_[idx];
}


/* path_start_to_end(unsigned end_node_index)
*  Takes in the index of the end node.
*  Each node points to its 'previous' node on the path (like a list). We walk this all the way back to the starting node
*/
vector<unsigned> Dijkstra::path_start_to_end(unsigned end_node_index) {

    vector<unsigned> path_to_end;
    unsigned curr_index = get_node_idx(end_node_index);

    // jump to the 'previous' node until we reach the start. Push back each node until we get to the start 
    while (path[curr_index].first != start_) {
        path_to_end.push_back(path[curr_index].first);          // path[i].first is the 'current node', which the path follows

        curr_index = get_node_idx(path[curr_index].second);     // path[i].second is the 'previous node', which we want to go to next
    }
    path_to_end.push_back(path[curr_index].first);

    // This traverses it backwards, so we need to reverse it to get it in start-end order 
    reverse(path_to_end.begin(), path_to_end.end());

    return path_to_end;
}


/* path_target_distance(double target_distance)
*  Takes a tartet distance, and returns the path that is closest to this target distance from the starting node.
*  This calls the 'path_start_to_end' function, which grabs the path to the desired node.
*/
vector<unsigned> Dijkstra::path_target_distance(double target_distance) {

    double closest_dist = DBL_MAX;
    unsigned target_node = 0;

    // loop through the distances_ vector. Once we find the node who's distance is closest to our target_distance, we return the path to that index (from start)
    for (unsigned i = 0; i < distances_.size(); i++ ) {
        double this_dist = abs(target_distance - distances_[i]) ;
        if (this_dist < closest_dist) {
            closest_dist = this_dist;
            target_node = i;
        }
    }

    return path_start_to_end(target_node);
}