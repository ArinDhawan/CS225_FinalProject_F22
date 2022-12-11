#include "print.h"
#include "sort.cpp"

/* print dataset to terminal */
void print(std::vector<Node> set){
    std::vector<Node> copy = set;
    sortSet(copy);
    for(auto node : copy){
        std::cout << node._idx << " : " << node._x << ", " << node._y << std::endl;

        for(auto edge : node._edges){
            std::cout << edge._start_node_idx << ", " << edge._end_node_idx << std::endl;
        }
    }
}

/* print function but to output file */
void print_to_file(std::string file_name, std::vector<Node> set){
    std::vector<Node> copy = set;
    sortSet(copy);

    std::ofstream output(file_name);
    if(!output.is_open()) return;
    
    for(auto node : copy){
        output << node._idx << " : " << node._x << ", " << node._y << std::endl;

        for(auto edge : node._edges){
            output  << edge._start_node_idx << ", "
                << edge._end_node_idx
                << std::endl;
        }
    }
    output.close();
}

/* print dataset in CSV format */
void print_node_file(std::string file_name, std::vector<Node> set){
    std::vector<Node> copy = set;
    sortSet(copy);
    
    std::ofstream output(file_name);
    if(!output.is_open()) return;
    
    for(auto node : copy){
        output << node._idx << " " << node._x << " " << node._y << std::endl;
    }
    output.close();
}

/* print dataset in CSV format */
void print_edge_file(std::string file_name, std::vector<Node> set){
    std::vector<Node> copy = set;
    sortSet(copy);

    std::ofstream output(file_name);
    if(!output.is_open()) return;

    for(auto node : copy){
        for(auto edge : node._edges){
            output << edge._idx << " "
                << edge._start_node_idx << " "
                << edge._end_node_idx << " "
                << edge._weight
                << std::endl;
        }
    }
    output.close();
}

//TODO finish function
/* return true if exact copies, print differences to output file */
bool compare_file(std::string file_name_out, std::string file_name_test, std::string file_name_orig){
    bool ret = false;

    std::ofstream output(file_name_out);
    if(!output.is_open()) return false;

    std::ifstream input_test(file_name_test), input_orig(file_name_orig);
    if(!input_test.is_open() || !input_orig.is_open()) return false;

    /* check */
    std::string str_test, str_orig;
    double temp_test, temp_orig;
    while(!input_test.eof() && !input_orig.eof()){
        std::getline(input_test, str_test);
        std::getline(input_orig, str_orig);
        std::stringstream s_t(str_test), s_o(str_orig);

        while(temp_test != '\n' && temp_orig != '\n'){
            s_t >> temp_test;
            s_o >> temp_orig;

            if(temp_test != temp_orig){
                output << str_test << str_orig << std::endl;
            }
        }
    }
    input_test.close();
    input_orig.close();
    output.close();

    return ret;
}