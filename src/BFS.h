#ifndef BFS_H
#define BFS_H


#include "Node.cpp"
#include "Edge.cpp"

std::vector<Node> makeDataSet(std::string file_name_node, std::string file_name_edge);
std::vector<Node> makeSubset(std::vector<Node> dataset);
std::pair<unsigned, double> getUserInput();

#endif