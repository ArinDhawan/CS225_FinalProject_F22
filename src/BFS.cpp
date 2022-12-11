#include "BFS.h"
#include "sort.h"

std::vector<Node> makeDataSet(std::string file_name_node, std::string file_name_edge){
    std::vector<Node> nodeSet = makeNodeSet(file_name_node);
    std::vector<Edge> edgeSet = makeEdgeSet(file_name_edge);
    std::vector<Node> ret = makeAdjSet(nodeSet, edgeSet);

    return ret;
}

std::vector<Node> makeNodeSet(std::string file_name_node){
    std::ifstream node_list;
    std::vector<Node> ret;

    /* open node file */
    node_list.open(file_name_node, std::ios_base::in);
    if(!node_list.is_open()){
        std::cout << "FAIL\nfile : BFS.cpp ; line : " << __LINE__ << std::endl;
        return std::vector<Node>();
    } 

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
        std::cout << "Line : " << __LINE__ << std::endl;
        std::cout << "node_idx : " << node_idx << std::endl;

        /* construct Node, push to ret */
        ret.push_back(Node(node_idx, latitude, longitude, std::vector<Edge>()));
    }
    /* close node file */
    node_list.close();

    /* return */
    return ret;
}

std::vector<Edge> makeEdgeSet(std::string file_name_edge){
    std::ifstream edge_list;
    std::vector<Edge> ret;

    /* open edge file */
    edge_list.open(file_name_edge, std::ios_base::in);
    if(!edge_list.is_open()){
        std::cout << "FAIL\nfile : BFS.cpp ; line : " << __LINE__ << std::endl;
        return std::vector<Edge>();
    } 

    /* parse edge file */
    while(!edge_list.eof()){

        /* init edge data */
        std::string str_edge;
        unsigned edge_idx;
        unsigned start_node_idx, end_node_idx;
        double weight;

        /* grab edge data */
        getline(edge_list, str_edge);
        std::stringstream s(str_edge);
        s >> edge_idx >> start_node_idx >> end_node_idx >> weight;

        /* mark */
        std::cout << "Line : " << __LINE__ << std::endl;
        std::cout << "edge_idx : " << edge_idx << std::endl;

        /* construct Edge */
        ret.push_back(Edge(edge_idx, start_node_idx, end_node_idx, weight));
    }
    /* close node file */
    edge_list.close();

    /* return */
    return ret;
}

std::vector<Node> makeAdjSet(std::vector<Node> nodeSet, std::vector<Edge> edgeSet){
    /* copy nodeSet to ret */
    std::vector<Node> ret = nodeSet;
    unsigned first, second;

    /* parse edgeSet */
    for(auto edge : edgeSet){
        first = std::min(edge._start_node_idx, edge._end_node_idx);
        second = std::max(edge._start_node_idx, edge._end_node_idx);
        
        ret[first]._edges.push_back(Edge(edge._idx, first, second, edge._weight));
        ret[second]._edges.push_back(Edge(edge._idx, second, first, edge._weight));
    }

    return ret;
}

std::vector<Node> makeSubset(std::vector<Node> dataset){
    /* null check */
    if(dataset.empty()){
        std::cout << "FAIL\nfile : BFS.cpp ; line : " << __LINE__ << std::endl;
        return std::vector<Node>();
    }

    /* init data */
    std::queue<Node> queue;
    std::vector<Node> ret;
    std::vector<unsigned> visited(dataset.size(), false);
    Node curr_node;
    unsigned new_node_idx;

    /* center globals */
    std::pair<unsigned, double> user = getUserInput();
    unsigned __CENTER_IDX = user.first;
    double __RADIUS_SQR = std::pow((double)(user.second), 2);

    /* push center node */
    queue.push(dataset[__CENTER_IDX]);
    visited[__CENTER_IDX] = true;
    while(!queue.empty()){
        /* push to ret + pop */
        ret.push_back(queue.front());
        curr_node = queue.front();
        queue.pop();

        /* parse adjacent nodes via front node's edge list */
        for(auto edge : curr_node._edges){
            /* get new_node_idx from edge */
            new_node_idx = (curr_node._idx == edge._start_node_idx) ? 
                edge._end_node_idx : edge._start_node_idx;

            /* check if new_node is visited */
            if(!visited[new_node_idx]){
                /* check if new node is within radius */
                if((std::pow(dataset[new_node_idx]._x - dataset[__CENTER_IDX]._x, 2)
                  + std::pow(dataset[new_node_idx]._y - dataset[__CENTER_IDX]._y, 2) 
                  <= __RADIUS_SQR)){
                    /* load to queue, mark visited */
                    queue.push(dataset[new_node_idx]);
                    visited[new_node_idx] = true;
                }
            }
        }
    }
    /* sort subset */
    sortSet(ret);

    /* return */
    return ret;
}

std::pair<unsigned, double> getUserInput(){
    /* get center node # */
    int user_node;
    std::cout << "ENTER CENTER NODE # : " << std::endl;
    std::cin >> user_node;

    /* get radius */
    double radius;
    std::cout << "ENTER RADIUS : " << std::endl;
    std::cin >> radius;
    /* Check if valid radius inpput */

    while(radius < 0){
        std::cout << "RADIUS CANT BE NEGATIVE, RETRY : " << std::endl;
        std::cin >> radius;
    }

    /* return */
    return std::pair<unsigned, double>(user_node, radius);
}
