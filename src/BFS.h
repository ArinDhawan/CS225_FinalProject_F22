#pragma once

#ifndef BFS_H
#define BFS_H

#include "Node.h"
#include "Edge.h"

/* Create a dataset of nodes from a given nodes file and edges file */
std::vector<Node> makeDataSet(std::string file_name_node, std::string file_name_edge);

/* Read text file and create a vector list of nodes */
std::vector<Node> makeNodeSet(std::string file_name_node);

/* Read text file and create a vector list of edges */
std::vector<Edge> makeEdgeSet(std::string file_name_edge);

/* Given vectors of nodes and edges combine them into a single vector of nodes */
std::vector<Node> makeAdjSet(std::vector<Node> nodeSet, std::vector<Edge> edgeSet);

/* Given a dataset of nodes create a smaller circular subset via user inputs  */
std::vector<Node> makeSubset(std::vector<Node> dataset);

/* Obtain the user's input for a (Unsign) center node and (Double) radius */
std::pair<unsigned, double> getUserInput();

#endif