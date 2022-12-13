#include "BFS.h"
#include "sort.h"

/* Create a dataset of nodes from a given nodes file and edges file */
std::vector<Node> makeDataSet(std::string file_name_node, std::string file_name_edge){

    //Build the nodes set
    std::vector<Node> nodeSet = makeNodeSet(file_name_node);
    //Build the edges set
    std::vector<Edge> edgeSet = makeEdgeSet(file_name_edge);

    //Combine the sets into an adjacnecy set
    std::vector<Node> ret = makeAdjSet(nodeSet, edgeSet);

    return ret;
}

/* Read text file and create a vector list of nodes */
std::vector<Node> makeNodeSet(std::string file_name_node){

    //Init return and node text file vars
    std::ifstream node_list;
    std::vector<Node> ret;

    //Open Node file
    node_list.open(file_name_node, std::ios_base::in);

    //Check if opening file failed
    if(!node_list.is_open()){
        std::cout << "FAILED TO OPEN FILE\n file: BFS.cpp, line: " << __LINE__ << std::endl;
        return std::vector<Node>();
    } 

    //Loop through node file && Build node list
    while(!node_list.eof()){

        //Init return and node vars
        std::string str_node;
        unsigned node_idx;
        double latitude, longitude;

        //Get node data
        std::getline(node_list, str_node);
        std::stringstream s(str_node);
        s >> node_idx >> latitude >> longitude;

        //Print out node data
        std::cout << "Line : " << __LINE__ << std::endl;
        std::cout << "node_idx : " << node_idx << std::endl;


        //Create and push new node to return vector
        ret.push_back(Node(node_idx, latitude, longitude, std::vector<Edge>()));
    }
    
    //Close the file
    node_list.close();

    return ret;
}

/* Read text file and create a vector list of edges */
std::vector<Edge> makeEdgeSet(std::string file_name_edge){

    //Init return and edge text file vars
    std::ifstream edge_list;
    std::vector<Edge> ret;

    //Open edge file
    edge_list.open(file_name_edge, std::ios_base::in);

    //Check if opening file failed
    if(!edge_list.is_open()){
        std::cout << "FAILED TO OPEN FILE\n file: BFS.cpp, line: " << __LINE__ << std::endl;
        return std::vector<Edge>();
    } 

    //Loop through edge file && Build edge list
    while(!edge_list.eof()){

        //Init return and edge vars
        std::string str_edge;
        unsigned edge_idx;
        unsigned start_node_idx, end_node_idx;
        double weight;

        //Get node data
        getline(edge_list, str_edge);
        std::stringstream s(str_edge);
        s >> edge_idx >> start_node_idx >> end_node_idx >> weight;

        //Print out node data
        std::cout << "Line : " << __LINE__ << std::endl;
        std::cout << "edge_idx : " << edge_idx << std::endl;


        //Create and push new node to return vector
        ret.push_back(Edge(edge_idx, start_node_idx, end_node_idx, weight));
    }

    //Close the file
    edge_list.close();

    return ret;
}

/* Given vectors of nodes and edges combine them into a single vector of nodes */
std::vector<Node> makeAdjSet(std::vector<Node> nodeSet, std::vector<Edge> edgeSet){
    
    //Copy nodes && declare vars
    std::vector<Node> ret = nodeSet;
    unsigned first, second;

    //Parse edgest && load edges into nodes
    for(auto edge : edgeSet){

        //Get the start and end nodes of the edge
        first = std::min(edge._start_node_idx, edge._end_node_idx);
        second = std::max(edge._start_node_idx, edge._end_node_idx);
        
        //Load edges into nodes
        ret[first]._edges.push_back(Edge(edge._idx, first, second, edge._weight));
        ret[second]._edges.push_back(Edge(edge._idx, second, first, edge._weight));
    }

    return ret;
}

/* Given a dataset of nodes create a smaller circular subset via user inputs  */
std::pair<unsigned, double> makeSubset(std::vector<Node>& subset, std::vector<Node> dataset){

    //Check for empty datasets
    if(dataset.empty()){
        std::cout << "FAIL\nfile: BFS.cpp, line: " << __LINE__ << std::endl;
        return std::pair<unsigned, double>();
    }

    //Init vars
    subset.clear();
    std::queue<Node> queue;
    std::vector<unsigned> visited(dataset.size(), false);
    Node curr_node;
    unsigned new_node_idx;

    //Get user input for center node and radius
    std::pair<unsigned, double> user = getUserInput();
    //Set center node index
    unsigned __CENTER_IDX = user.first;
    //Set squared radius (Easier to compare squared distance instead of square root)
    double __RADIUS_SQR = std::pow((double)(user.second), 2);

    //Push center node to queue and mark visisted
    queue.push(dataset[__CENTER_IDX]);
    visited[__CENTER_IDX] = true;

    //Loop through queue && 
    while(!queue.empty()){

        //Pop from queue and add it to the return vector
        subset.push_back(queue.front());
        curr_node = queue.front();
        queue.pop();

        //Parse through adjacent nodes via the current node's edge list
        for(auto edge : curr_node._edges){

            //Get new node's idex
            new_node_idx = (curr_node._idx == edge._start_node_idx) ? 
                edge._end_node_idx : edge._start_node_idx;

            //Check if new node has been visited
            if(!visited[new_node_idx]){

                //Check if new node is within the radius (Squared to compare more easily)
                if((std::pow(dataset[new_node_idx]._x - dataset[__CENTER_IDX]._x, 2)
                  + std::pow(dataset[new_node_idx]._y - dataset[__CENTER_IDX]._y, 2) 
                  <= __RADIUS_SQR)){

                    //Add node to queue and mark visited
                    queue.push(dataset[new_node_idx]);
                    visited[new_node_idx] = true;
                }
            }
        }
    }
    //Sort the subset
    sortSet(subset);

    return user;
}

/* Obtain the user's input for a (Unsign) center node and (Double) radius */
std::pair<unsigned, double> getUserInput(){

    //Get center node
    int user_node = -1;
    std::cout << "ENTER CENTER NODE # : " << std::endl;
    std::cin >> user_node;

    //Check if valid node
    while(user_node < 0){

        //Ask for new valid node
        std::cout << "NODE CANT BE NEGATIVE, RETRY : " << std::endl;
        std::cin >> user_node;
    }

    //Get radius
    double radius = -1;
    std::cout << "ENTER RADIUS : " << std::endl;
    std::cin >> radius;

    //Check if valid radius
    while(radius < 0){

        //Ask for new valid radius
        std::cout << "RADIUS CANT BE NEGATIVE, RETRY : " << std::endl;
        std::cin >> radius;
    }

    return std::pair<unsigned, double>(user_node, radius);
}
