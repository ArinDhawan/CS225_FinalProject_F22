#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <utility>
#include <string>

/* Edge Class */
class Edge {
    public:
        Edge(unsigned end_node_idx, double weight, Edge * next){
            _end_node_idx = end_node_idx;
            _weight = weight;
            _next = next;
        }

        Edge(const Edge & other){
            _end_node_idx = other._end_node_idx;
            _weight = other._weight;
            _next = other._next;
        }

        ~Edge(){
            /* mark */
            //std::cout << "Line : " << __LINE__ << std::endl;

            if(!_next) return;
            _next->~Edge();
            delete _next;
            _next = NULL;
        }

        Edge* operator=(const Edge * other){
            /* mark */
            //std::cout << "Line : " << __LINE__ << std::endl;

            this->~Edge();
            _end_node_idx = other->_end_node_idx;
            _weight = other->_weight;
            _next = (other->_next) ? new Edge(*(other->_next)) : NULL;
            return this;
        }

        unsigned _end_node_idx;
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

        Node* operator=(const Node * other){
            if(!other) return NULL;

            /* mark */
            //std::cout << "Line : " << __LINE__ << std::endl;

            _x = other->_x;
            _y = other->_y;
            _edge = (other->_edge) ? new Edge(*(other->_edge)) : NULL;
            return this;
        }

        double _x, _y;
        Edge * _edge;
};

/* Convert text files to a friendlier adjancency list */
std::vector<Node*> makeDataSet(){
    std::ifstream node_list, edge_list;
    std::vector<Edge*> edges;
    std::vector<Node*> ret;

    /* open node file */
    node_list.open("datasets/small_nodes.txt", std::ios_base::in);
    if(!node_list.is_open()) return std::vector<Node*>();

    /* parse node file */
    while(node_list){

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
        edge_list.open("datasets/small_edges.txt", std::ios_base::in);
        if(!edge_list.is_open()) return std::vector<Node*>();

        /* init edge data */
        std::string str_edge;
        unsigned edge_idx;
        unsigned start_node_idx, end_node_idx;
        double weight;

        /* goto start_node */
        do{
            /* mark */
            //std::cout << "Line : " << __LINE__ << std::endl;

            std::getline(edge_list, str_edge);
            std::stringstream s(str_edge);
            s >> edge_idx >> start_node_idx >> end_node_idx >> weight;
        }while(!edge_list.eof() && start_node_idx < node_idx);

        /* parse edge file */
        while(!edge_list.eof() && start_node_idx == node_idx){

            /* construct Edge (recur call) */
            edges.push_back(new Edge(end_node_idx, weight, NULL));

            /* grab edge data */
            getline(edge_list, str_edge);
            std::stringstream s(str_edge);
            s >> edge_idx >> start_node_idx >> end_node_idx >> weight;

            /* mark */
            //std::cout << "Line : " << __LINE__ << std::endl;
        }

        /* close edge file */
        edge_list.close();

        /* construct edge list from edge vector */
        for(unsigned i = 1; i < edges.size(); i++)
            edges[i - 1]->_next = edges[i];

        /* construct Node, push to ret */
        ret.push_back(new Node(latitude, longitude, edges[0]));

        /* delete edges vector*/
        edges[0]->~Edge();
        edges.clear();
    }
    /* close node file */
    node_list.close();

    /* return */
    return ret;
}

// Edge * getEdge(unsigned base_idx, std::fstream edge_list){
//     /* init edge data */
//     char * str_edge;
//     unsigned edge_idx;
//     unsigned start_node_idx, end_node_idx;
//     double weight;

//     /* grab edge data */
//     edge_list.getline(str_edge, 50, '\n');
//     edge_list >> edge_idx >> start_node_idx >> end_node_idx >> weight;

//     /* fail check */
//     if(start_node_idx != base_idx) return NULL;

//     /* construct Edge (recur call) */
//     Edge * ret = new Edge(end_node_idx, weight, getEdge(base_idx, edge_list)); //TODO: WHY NO COMPILE??

//     /* return */
//     return ret;
// }

// Node * getNode(std::fstream node_list, std::fstream edge_list){
//     /* init node data */
//     char * str_node;
//     unsigned node_idx;
//     double latitude, longitude;

//     /* grab node data */
//     node_list.getline(str_node, 50,'\n');
//     node_list >> node_idx >> latitude >> longitude;

//     /* construct Node */
//     Node * ret = new Node(latitude, longitude, getEdge(node_idx, edge_list)); //TODO: WHY NO COMPILE??

//     /* return */
//     return ret;
// }

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
    double __RADIUS_SQR = user.second * user.second;

    /* push center node */
    queue.push(new Node(*dataset[__CENTER_IDX]));
    visited.emplace(__CENTER_IDX);
    while(!queue.empty()){
        /* push to ret + pop */
        ret.push_back(queue.front());
        queue.pop();

        /* parse adjacent nodes via front node's edge list */
        edge_list = (ret.back())->_edge;
        while(edge_list){
            /* check if adj node is visited OR OUTSIDE RADIUS */
            if(visited.find(edge_list->_end_node_idx) == visited.end() && (dataset[edge_list->_end_node_idx]->_x - 
            dataset[__CENTER_IDX]->_x + dataset[edge_list->_end_node_idx]->_y - dataset[__CENTER_IDX]->_y <= __RADIUS_SQR)){
                /* push unvisited adj node + mark as visited */
                queue.push(new Node(*dataset[edge_list->_end_node_idx]));
                visited.emplace(edge_list->_end_node_idx);
            }
            edge_list = edge_list->_next;
        }
    }

    /* return :) */
    return ret;
}


int main() {
    /* construct adj list from txt files */
    std::vector<Node*> dataset = makeDataSet();
    if(dataset == std::vector<Node*>()){
        std::cout << "FAIL" << std::endl;
    }
    else{
        std::cout << "BETTER!!" << std::endl;
    }

    /* constuct 'circle' subset */
    std::vector<Node*> subset = BFS(dataset);

    /* printout subset */
    for(auto elem : subset){
        std::cout << elem->_x << ", " << elem->_y << std::endl;
    }

    return 0;
}