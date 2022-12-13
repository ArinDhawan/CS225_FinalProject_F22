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
#include "../src/render.h"
#include "dijkstra.h"

int main() {
    //TEST SUITE 1:
    /*Vector String Testcase Files*/
    std::vector<std::pair<std::string, std::string>> file_list;

    /* Load vector with test cases - Comment/Uncomment test cases to select them! */
    //file_list.push_back(std::make_pair("../datasets/verysmall_nodes.txt", "../datasets/verysmall_edges.txt"));
    //file_list.push_back({"../datasets/small_nodes.txt", "../datasets/small_edges.txt"});
    file_list.push_back({"../datasets/california_nodes.txt", "../datasets/california_edges.txt"});
    //file_list.push_back({"../datasets/san_francisco_nodes.txt", "../datasets/san_francisco_edges.txt"});

    /*Declare vars*/
    std::vector<Node> subset;  
    std::vector<Node> dataset;  

    std::string curr_nodes, curr_edges;
    for(size_t i = 0; i < file_list.size(); i++){
        curr_nodes = file_list[i].first;
        curr_edges = file_list[i].second;

        /* construct adj list from txt files */
        dataset = makeDataSet(curr_nodes, curr_edges);
        
        /* constuct 'circle' subset */
        subset = makeSubset(dataset);

        /* call dijkstra */
        Dijkstra d(dataset, 0);
        d.solve();

        /* render PNG */
        render(subset, d.path_start_to_end(50), 1000, 5).writeToFile("out.png");
    }

    return 0;
}