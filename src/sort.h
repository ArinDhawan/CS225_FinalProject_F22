#include "Node.h"

#pragma once

/* sortSet helper */
int getIdx(std::vector<Node>& arr, int low, int high);

/* sortSet helper */
void quickSort(std::vector<Node>& arr, int low, int high);

/* sort given dataset by Node Idx */
void sortSet(std::vector<Node>& dataset);