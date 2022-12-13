#pragma once

#ifndef BFS_H
#define BFS_H

#include "Node.h"
#include "Edge.h"

/*
    Create a dataset of nodes from a given nodes file and edges file.
    INPUTS: dataset text file of nodes, dataset text file of edges
    OUTPUTS: vector node dataset of combine nodes and edges
*/
std::vector<Node> makeDataSet(std::string file_name_node, std::string file_name_edge);

/*
    Read text file and create a vector list of nodes.
    INPUTS: dataset text file of nodes
    OUTPUTS: vector list of nodes
*/
std::vector<Node> makeNodeSet(std::string file_name_node);

/*
    Read text file and create a vector list of edges.
    INPUTS: dataset text file of edges
    OUTPUTS: vector list of edges
*/
std::vector<Edge> makeEdgeSet(std::string file_name_edge);

/*
    Given vectors of nodes and edges combine them into a single vector of nodes
    INPUT: vector list of nodes, vector list of edges
    OUTPUT: combined vector list of nodes with edges per node
*/
std::vector<Node> makeAdjSet(std::vector<Node> nodeSet, std::vector<Edge> edgeSet);

/*
    Given a dataset of nodes create a smaller circular subset via user inputs.
    INPUTS: combined vector list of nodes with edges per node
    OUTPUTS: subset of a vector list of nodes with edges per node
*/
std::pair<unsigned, double> makeSubset(std::vector<Node>& subset, std::vector<Node> dataset);

/*
    Obtain the user's input for a (Unsign) center node and (Double) radius
    INPUTS: none (User terminal input)
    OUTPUTS: unsigned node index and double radius pair
*/
std::pair<unsigned, double> getUserInput();

#endif