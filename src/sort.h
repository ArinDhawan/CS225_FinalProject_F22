#pragma once

#ifndef SORT_H
#define SORT_H

#include "Node.h"

/* 
    Finds the pivot point and swaps nodes.
    INPUTS: node vector dataset, start index, end index
    OUTPUTS: index of pivot node to continue sorting
*/
int getIdx(std::vector<Node>& arr, int low, int high);

/* 
    A recursive quick sort algorithm helper function.
    INPUTS: node vector dataset, start index, end index 
    OUTPUTS: void
*/
void quickSort(std::vector<Node>& arr, int low, int high);

/* 
    Sort a dataset of Nodes by their indexs from least to greatest.
    INPUTS: node vector dataset
    OUTPUTS: void
*/
void sortSet(std::vector<Node>& dataset);

#endif