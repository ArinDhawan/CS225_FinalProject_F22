#include "print.h"
#include "sort.h"

/* Print a dataset to terminal */
void print(std::vector<Node> set){

    //Copy the dataset
    std::vector<Node> copy = set;

    //Loop through nodes in datasets && print to terminal
    for(auto node : copy){

        //Print: NODE_INDEX : X : Y
        std::cout << node._idx << " : " << node._x << ", " << node._y << std::endl;

        //Parse connected edges && print edges to terminal
        for(auto edge : node._edges){

            //Print: START_INDEX, END_INDEX
            std::cout << edge._start_node_idx << ", " << edge._end_node_idx << std::endl;
        }
    }
}

/* Print a dataset to a text file */
void print_to_file(std::string file_name, std::vector<Node> set){

    //Copy datasets
    std::vector<Node> copy = set;

    //Open output stream to print to file
    std::ofstream output(file_name);

    //Check if file failed to open
    if(!output.is_open()) return;
    
    //Parse nodes in dataset
    for(auto node : copy){

        //Print: NODE_INDEX : X, Y
        output << node._idx << " : " << node._x << ", " << node._y << std::endl;

        //Parse edges connected to node
        for(auto edge : node._edges){

            //Print: START_INDEX, END INDEX
            output  << edge._start_node_idx << ", " << edge._end_node_idx << std::endl;
        }
    }
    //Close file
    output.close();
}

/* Print node dataset in CSV format to a text file */
void print_node_file(std::string file_name, std::vector<Node> set){

    //Copy dataset
    std::vector<Node> copy = set;

    //Open output stream to print to file
    std::ofstream output(file_name);

    //Check if file failed to open
    if(!output.is_open()) return;
    
    //Parse nodes in dataset
    for(auto node : copy){
        //Print: NODE_INDEX : X, Y
        output << node._idx << " " << node._x << " " << node._y << std::endl;
    }
    //Close file
    output.close();
}

/* Print edges dataset in CSV format to a text file */
void print_edge_file(std::string file_name, std::vector<Node> set){

    //Copy dataset
    std::vector<Node> copy = set;

    //Open output stream to print to file
    std::ofstream output(file_name);

    //Check if file failed to open
    if(!output.is_open()) return;

    //Parse nodes in dataset
    for(auto node : copy){

        //Parse edges connected to node
        for(auto edge : node._edges){

            //Print edge to file
            output << edge._idx << " "
                << edge._start_node_idx << " "
                << edge._end_node_idx << " "
                << edge._weight
                << std::endl;
        }
    }
    //Close file
    output.close();
}