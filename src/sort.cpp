#include "sort.h"

/* Finds the pivot point and swaps nodes. */
int getIdx(std::vector<Node>& arr, int low, int high){

    //Find the pivot node's index
    int pivot_node_idx = arr[high]._idx;
    int i = low - 1;

    //Loop from low to high && swap nodes
    for(int j = low; j < high; j++){

        //Check if node should be swapped
        if((int)arr[j]._idx < pivot_node_idx){

            //Swap nodes
            std::swap(arr[++i], arr[j]);
        }
    }

    //Swap nodes
    std::swap(arr[i + 1], arr[high]);

    //Return pivot node index
    return i + 1;
}

/* Quick sort algorithm helper function */
void quickSort(std::vector<Node>& arr, int low, int high){

    //Check if low index is smaller than high index
    if(low < high){

        //Get index of pivot point
        unsigned idx = getIdx(arr, low, high);

        //Recursive call to continue sorting
        quickSort(arr, low, idx - 1);
        quickSort(arr, idx + 1, high);
    }
}

/* Sort a dataset of Nodes by their indexs from least to greatest */
void sortSet(std::vector<Node>& dataset){

    //Call the quick sort algorithm helper function
    quickSort(dataset, 0, dataset.size() - 1);

}