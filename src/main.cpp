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

/* Edge Class */
class Edge {
    public:
        Edge(unsigned start_node_idx, unsigned end_node_idx, double weight, Edge * next){
            _start_node_idx = start_node_idx;
            _end_node_idx = end_node_idx;
            _weight = weight;
            _next = next;
        }

        Edge(const Edge & other){
            _start_node_idx = other._start_node_idx;
            _end_node_idx = other._end_node_idx;
            _weight = other._weight;
            _next = other._next;
        }

        ~Edge(){
            /* mark */
            //std::cout << "Line : " << __LINE__ << std::endl;

            if(!this || !_next) return;
            _next->~Edge();
            delete _next;
            _next = NULL;
        }

        unsigned _start_node_idx, _end_node_idx;
        double _weight;
        Edge * _next;
};

/* Node Class */
class Node {
    public:
        Node(double latitude, double longitude, Edge * edge){
            _x = latitude;
            _y = longitude;
            _edge = edge;
        }

        Node(const Node & other){
            _x = other._x;
            _y = other._y;
            _edge = other._edge;
        }

        ~Node(){
            _edge->~Edge();
        }

        double _x, _y;
        Edge * _edge;
};

/* Convert text files to a friendlier adjancency list */
std::vector<Node*> makeDataSet(){
    std::ifstream node_list, edge_list;
    std::vector<Edge> edges;
    std::vector<Node*> ret;

    /* open node file */
    node_list.open("datasets/verysmall_nodes.txt", std::ios_base::in);
    if(!node_list.is_open()) return std::vector<Node*>();

    /**
     * @brief load node vector from txt file
     * 1. grab node data with getline()
     * 2. get edge vector SEE NEXT @brief
     * 3. construct linked-list from edge vector
     * 4. load head of list into node obj with node data
     * 5. repeat per node
     */

    /* parse node file */
    while(!node_list.eof()){

        /* init node data */
        std::string str_node;
        unsigned node_idx;
        double latitude, longitude;

        /* grab node data */
        std::getline(node_list, str_node);
        std::stringstream s(str_node);
        s >> node_idx >> latitude >> longitude;

        /* mark */
        //std::cout << "Line : " << __LINE__ << std::endl;
        //std::cout << "node_idx : " << node_idx << std::endl;

        /* open edge file */
        edge_list.open("datasets/verysmall_edges.txt", std::ios_base::in);
        if(!edge_list.is_open()) return std::vector<Node*>();

        /* init edge data */
        std::string str_edge;
        unsigned edge_idx;
        unsigned start_node_idx, end_node_idx;
        double weight;

        /** 
         * @brief load edges vector from txt file 
         * pt1 : grab edges pointing TO target node
         * pt2 : grab edges pointing FROM target node
         */

        /* parse edge file pt1 */
        do{
            /* grab edge data */
            std::getline(edge_list, str_edge);
            std::stringstream s(str_edge);
            s >> edge_idx >> start_node_idx >> end_node_idx >> weight;

            /* if edge TO target --> load edge */
            if(end_node_idx == node_idx){
                edges.push_back(Edge(end_node_idx, start_node_idx, weight, NULL));

                /* mark */
                // std::cout << "Line : " << __LINE__ << std::endl;
                // std::cout << "node_idxes : " << end_node_idx << ", " << start_node_idx << std::endl;
            }

        }while(!edge_list.eof() && start_node_idx < node_idx);

        /* parse edge file pt2 */
        while(start_node_idx == node_idx){

            /* construct Edge */
            edges.push_back(Edge(start_node_idx, end_node_idx, weight, NULL));

            /* mark */
            // std::cout << "Line : " << __LINE__ << std::endl;
            // std::cout << "node_idxes : " << start_node_idx << ", " << end_node_idx << std::endl;

            /* file break */
            if(edge_list.eof()) break;

            /* grab edge data */
            getline(edge_list, str_edge);
            std::stringstream s(str_edge);
            s >> edge_idx >> start_node_idx >> end_node_idx >> weight;
        }
        /* close edge file */
        edge_list.close();

        /* construct edge list from edge vector */
        Edge * edge_list_head = (!edges.empty()) ? new Edge(edges[0]) : NULL, *edge_list_ptr = edge_list_head;
        for(unsigned i = 1; i < edges.size(); i++){
            edge_list_ptr->_next = new Edge(edges[i]);
            edge_list_ptr = edge_list_ptr->_next;
        }

        /* construct Node, push to ret */
        ret.push_back(new Node(latitude, longitude, edge_list_head)); //TODO: MEM LEAK HERE

        /* delete edges vector */
        edges.clear();
    }
    /* close node file */
    node_list.close();

    /* return */
    return ret;
}

std::pair<unsigned, double> getUserInput(){
    /* get center node # */
    unsigned user_node;
    std::cout << "ENTER CENTER NODE # : " << std::endl;
    std::cin >> user_node;

    /* get radius */
    double radius;
    std::cout << "ENTER RADIUS : " << std::endl;
    std::cin >> radius;

    /* return */
    return std::pair<unsigned, double>({user_node, radius});
}

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

void printSet(std::vector<Node*> set){
    for(auto node : set){
        Edge * ptr = node->_edge;

        if(ptr){
            std::cout << ptr->_start_node_idx << " : " << node->_x << ", " << node->_y << std::endl;
        }
        else{
            std::cout << "UNKNOWN" << " : " << node->_x << ", " << node->_y << std::endl;
        }
        
        while(ptr){
            std::cout << ptr->_start_node_idx << ", " << ptr->_end_node_idx << std::endl;
            ptr = ptr->_next;
        }
    }
}

void deleteSet(std::vector<Node*> set){
    for(auto it = set.begin(); it != set.end(); it++){
        (*it)->_edge->~Edge();
    }
}


int main() {
    /* construct adj list from txt files */
    std::vector<Node*> dataset = makeDataSet();

    printSet(dataset);

    /* constuct 'circle' subset */
    std::vector<Node*> subset = BFS(dataset);

    printSet(subset);

    /* delete */
    deleteSet(dataset);
    deleteSet(subset);

    return 0;
}