#pragma once

#ifndef BFS_H
#define BFS_H


#include "Node.h"
#include "Edge.h"

std::vector<Node> makeDataSet(std::string file_name_node, std::string file_name_edge);

std::vector<Node> makeNodeSet(std::string file_name_node);

std::vector<Edge> makeEdgeSet(std::string file_name_edge);

std::vector<Node> makeAdjSet(std::vector<Node> nodeSet, std::vector<Edge> edgeSet);

std::vector<Node> makeSubset(std::vector<Node> dataset);

std::pair<unsigned, double> getUserInput();

#endif