#include "Node.h"

#pragma once

/* print dataset to terminal */
void print(std::vector<Node> set);

/* print function but to output file */
void print_to_file(std::string file_name, std::vector<Node> set);

/* print dataset in CSV format */
void print_node_file(std::string file_name, std::vector<Node> set);

/* print dataset in CSV format */
void print_edge_file(std::string file_name, std::vector<Node> set);

//TODO finish function
/* return true if exact copies, print differences to output file */
bool compare_file(std::string file_name_out, std::string file_name_test, std::string file_name_orig);