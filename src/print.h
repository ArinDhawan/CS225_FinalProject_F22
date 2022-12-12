#pragma once

#ifndef PRINT_H
#define PRINT_H

#include "Node.h"

/* Print a dataset to terminal */
void print(std::vector<Node> set);

/* Print a dataset to a text file */
void print_to_file(std::string file_name, std::vector<Node> set);

/* Print node dataset in CSV format to a text file */
void print_node_file(std::string file_name, std::vector<Node> set);

/* Print edges dataset in CSV format to a text file */
void print_edge_file(std::string file_name, std::vector<Node> set);

#endif