#include "BFS.h"
#include "main.cpp"

std::vector<Node*> BFS(std::vector<Node*> dataset){
    /* init data */
    std::vector<Node*> ret;
    std::unordered_set<unsigned> visited;
    std::queue<Node*> queue;
    Edge * edge_list;

    /* center globals */
    std::pair<unsigned, double> user = getUserInput();
    unsigned __CENTER_IDX = user.first;
    double __RADIUS_SQR = std::pow((double)(user.second), 2);

    /* push center node */
    queue.push(new Node(*dataset[__CENTER_IDX])); //TODO: MEM LEAK HERE
    visited.insert(__CENTER_IDX);
    while(!queue.empty()){
        /* push to ret + pop */
        ret.push_back(new Node(*queue.front())); //TODO: MEM LEAK HERE
        queue.pop();

        /* parse adjacent nodes via front node's edge list */
        edge_list = (ret.back())->_edge;
        while(edge_list){
            /* check if adj node is visited OR OUTSIDE RADIUS */
            if(visited.find(edge_list->_end_node_idx) == visited.end() && (std::pow(dataset[edge_list->_end_node_idx]->_x - 
            dataset[__CENTER_IDX]->_x, 2) + std::pow(dataset[edge_list->_end_node_idx]->_y - dataset[__CENTER_IDX]->_y, 2) <= __RADIUS_SQR)){
                /* push unvisited adj node + mark as visited */
                queue.push(new Node(*dataset[edge_list->_end_node_idx])); //TODO: MEM LEAK HERE
                visited.insert(edge_list->_end_node_idx);
            }
            edge_list = edge_list->_next;
        }
    }

    /* return :) */
    return ret;
}