#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>
#include <exception>
#include <catch2/catch_test_macros.hpp>
#include "../lib/cs225/PNG.h"
#include "../src/Node.h"
#include "../src/BFS.h"
#include "../src/print.h"
#include "../src/render.h"
#include "dijkstra.h"

using std::cout;

TEST_CASE("General Make Tests", "[Test1]"){
    std::vector<int> vec = {1, 2, 3};
    REQUIRE(vec.size() == 3);
}

TEST_CASE("DatasetVerySmall", "[Test2]") {

    std::vector<std::pair<std::string, std::string>> file_list;
    file_list.push_back({"../datasets/verysmall_nodes.txt", "../datasets/verysmall_edges.txt"});

    /*Declare vars*/
    std::vector<Node> subset;  
    std::vector<Node> dataset;  

    std::string curr_nodes, curr_edges;
    for(size_t i = 0; i < file_list.size(); i++){
        curr_nodes = file_list[i].first;
        curr_edges = file_list[i].second;

        //Testing BFS :
        /* construct adj list from txt files */
        dataset = makeDataSet(curr_nodes, curr_edges);

        /* checking size of dataset */
        REQUIRE(dataset.size() == 9);

        unsigned y = 0;
        for (auto& i : dataset) {
            /* checking every single node_idx of the dataset */
             REQUIRE(i._idx == y);
             y++;
        }

        //TODO: Testing MakeSubset : 
        /* constuct 'circle' subset */
        Node CENTER, CURR;
        Dijkstra PATH;
        std::vector<Node> subset;
        std::pair<unsigned, double> subset_user_data = makeSubset(subset, dataset);
        unsigned CENTER_IDX = subset_user_data.first;
        double RADIUS_SQR = std::pow(subset_user_data.second, 2);

        /* check subset */
        CENTER = dataset[CENTER_IDX];
        for(auto sub_node : subset){
            CURR = dataset[sub_node._idx];

            /* check that SUB_NODE is within RADIUS distance to CENTER */
            REQUIRE(std::pow(CURR._x - CENTER._x, 2) + std::pow(CURR._x - CENTER._x, 2) <= RADIUS_SQR);

            /* check that path exists from SUB_NODE to CENTER */
            PATH = Dijkstra(dataset, CENTER_IDX);
            PATH.solve();
            REQUIRE(PATH.get_distance_at_node(sub_node._idx) != UINT_MAX);

            /* check that all nodes in path are within RADIUS distance to CENTER */
            for(auto path_idx : PATH.path_start_to_end(sub_node._idx)){
                CURR = dataset[path_idx];
                REQUIRE(std::pow(CURR._x - CENTER._x, 2) + std::pow(CURR._x - CENTER._x, 2) <= RADIUS_SQR);
            }
        }

        
        //Testing Dijkstra: 
        /* call dijkstra */
        Dijkstra d(dataset, 0);
        d.solve();

        std::vector<unsigned> x  = d.path_start_to_end(7);
        std::vector<unsigned> dijkstrasol = {0,6,5,7};  //Solution for the Dijkstra's algo for our very small file  
        REQUIRE(x == dijkstrasol);



        //TODO: Testing RenderPNG : 
        /* render PNG */
        //render(subset, d.path_start_to_end(50), 1000, 5).writeToFile("out.png");

    }
}
TEST_CASE("DatasetSmall", "[Test3]") {
    std::vector<std::pair<std::string, std::string>> file_list;
    file_list.push_back({"../datasets/small_nodes.txt", "../datasets/small_edges.txt"});
     /*Declare vars*/
    std::vector<Node> subset;  
    std::vector<Node> dataset;  

    std::string curr_nodes, curr_edges;
    for(size_t i = 0; i < file_list.size(); i++){
        curr_nodes = file_list[i].first;
        curr_edges = file_list[i].second;

        //Testing BFS :
        /* construct adj list from txt files */
        dataset = makeDataSet(curr_nodes, curr_edges);

        /* checking size of dataset */
        REQUIRE(dataset.size() == 1001);
        unsigned y = 0;
        for (auto& i : dataset) {
            /* checking every single node_idx of the dataset */
             REQUIRE(i._idx == y);
             y++;
        }


        //TODO: Testing RenderPNG : 
        /* render PNG */
        //render(subset, d.path_start_to_end(50), 1000, 5).writeToFile("out.png");
    }
}

TEST_CASE("SanFrancisco", "[Test4]") {
    std::vector<std::pair<std::string, std::string>> file_list;
    file_list.push_back({"../datasets/san_francisco_nodes.txt", "../datasets/san_francisco_edges.txt"});
     /*Declare vars*/
    std::vector<Node> subset;  
    std::vector<Node> dataset;  

    std::string curr_nodes, curr_edges;
    for(size_t i = 0; i < file_list.size(); i++){
        curr_nodes = file_list[i].first;
        curr_edges = file_list[i].second;

        //Testing BFS :
        /* construct adj list from txt files */
        dataset = makeDataSet(curr_nodes, curr_edges);

        /* checking size of dataset */
        REQUIRE(dataset.size() == 174956);
        unsigned y = 0;
        for (auto& i : dataset) {
            /* checking every single node_idx of the dataset */
             REQUIRE(i._idx == y);
             y++;
        }


        //TODO: Testing RenderPNG : 
        /* render PNG */
        //render(subset, d.path_start_to_end(50), 1000, 5).writeToFile("out.png");
    }
}

TEST_CASE("California", "[Test5]") {
    std::vector<std::pair<std::string, std::string>> file_list;
    file_list.push_back({"../datasets/california_nodes.txt", "../datasets/california_edges.txt"});
     /*Declare vars*/
    std::vector<Node> subset;  
    std::vector<Node> dataset;  

    std::string curr_nodes, curr_edges;
    for(size_t i = 0; i < file_list.size(); i++){
        curr_nodes = file_list[i].first;
        curr_edges = file_list[i].second;

        //Testing BFS :
        /* construct adj list from txt files */
        dataset = makeDataSet(curr_nodes, curr_edges);
    
        /* checking size of dataset */
        REQUIRE(dataset.size() == 21048);

        unsigned y = 0;
        for (auto& i : dataset) {
            /* checking every single node_idx of the dataset */
             REQUIRE(i._idx == y);
             y++;
        }


        //TODO: Testing RenderPNG : 
        /* render PNG */
        //render(subset, d.path_start_to_end(50), 1000, 5).writeToFile("out.png");
    }
}









