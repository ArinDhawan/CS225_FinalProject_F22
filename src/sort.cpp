#include "sort.h"

/* sortSet helper */
int getIdx(std::vector<Node>& arr, int low, int high){
    int pivot_node_idx = arr[high]._idx;
    int i = low - 1;

    for(int j = low; j < high; j++){
        if((int)arr[j]._idx < pivot_node_idx){
            std::swap(arr[++i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

/* sortSet helper */
void quickSort(std::vector<Node>& arr, int low, int high){
    if(low < high){
        unsigned idx = getIdx(arr, low, high);
        quickSort(arr, low, idx - 1);
        quickSort(arr, idx + 1, high);
    }
}

/* sort given dataset by Node Idx */
void sortSet(std::vector<Node>& dataset){
    /* call quick sort algo */
    quickSort(dataset, 0, dataset.size() - 1);
}