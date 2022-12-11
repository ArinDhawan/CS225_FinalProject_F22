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
#include "../lib/cs225/PNG.h"
#include "../src/Node.h"
#include "../src/BFS.h"
#include "../src/print.h"

int main() {
    // std::cout << "Fuck you Fuck fuck you1!!!" << std::endl;

    //TEST SUITE 1:
    /*Vector String Testcase Files*/
    std::vector<std::pair<std::string, std::string>> file_list;

    // /* Load vector with test cases - Comment/Uncomment test cases to select them! */
    file_list.push_back(std::make_pair("../datasets/verysmall_nodes.txt", "../datasets/verysmall_edges.txt"));
    // //file_list.push_back({"datasets/verysmall_nodes.txt", "datasets/verysmall_edges.txt"});
    // //file_list.push_back({"datasets/small_nodes.txt", "datasets/small_edges.txt"});
    // // file_list.push_back({"datasets/california_nodes.txt", "datasets/california_edges.txt"});
    // // file_list.push_back({"datasets/san_francisco_nodes.txt", "datasets/san_francisco_edges.txt"});

    /*Declare vars*/
    std::vector<Node> subset;  
    std::vector<Node> dataset;  

    std::string curr_nodes, curr_edges;
    for(size_t i = 0; i < file_list.size(); i++){
        curr_nodes = file_list[i].first;
        curr_edges = file_list[i].second;

        /* construct adj list from txt files */
        dataset = makeDataSet(curr_nodes, curr_edges);
        
        /* print to console */
        print(dataset);

        /* constuct 'circle' subset */
        subset = makeSubset(dataset);

        /* make output file */
        //print_node_file(curr_nodes.substr(curr_nodes.find('/') + 1, curr_nodes.find_last_of('.') - curr_nodes.find('/')) + "output.txt", subset);
        //print_edge_file(curr_edges.substr(curr_edges.find('/') + 1, curr_edges.find_last_of('.') - curr_edges.find('/')) + "output.txt", subset);

        /* print to console */
        print(subset);

        /* compare to input file */
        //compare_file("compare_node.txt", curr_nodes, curr_nodes.substr(curr_nodes.find('/') + 1, curr_nodes.find_last_of('_') - curr_nodes.find('.')) + "output.txt");
        //compare_file("compare_edge.txt", curr_edges, curr_edges.substr(curr_edges.find('/') + 1, curr_edges.find_last_of('_') - curr_edges.find('.')) + "output.txt");

        /* delete */
        //deleteSet(dataset);
        //deleteSet(subset);

    }

    return 0;
}