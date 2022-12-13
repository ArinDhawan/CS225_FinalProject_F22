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
    //PRE-MADE INSTRUCTIONS FOR MAIN:
    /*Vector String Testcase Files*/
    std::vector<std::pair<std::string, std::string>> file_list;

    /* Load vector with custom database*/
    std::string x;
    std::cout << "Enter node file path:"; 
    std::cin >> x;

    std::string y;
    std::cout << "Enter edge file path:";
    std::cin >> y;
    file_list.push_back({x,y});

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
        std::vector<Node> subset;
        std::pair<unsigned, double> subset_user_data = makeSubset(subset, dataset);

        /* call dijkstra */
        Dijkstra d(dataset, 0);
        d.solve();

        /* render PNG */
        render(subset, d.path_start_to_end(50), 1000, 5).writeToFile("out.png");
    }

    return 0;
}