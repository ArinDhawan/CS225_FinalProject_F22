#include "render.h"
#include "BFS.cpp"

/* render given dataset as PNG of dim side_size by side_size */
cs225::PNG render(std::vector<Node> dataset, unsigned side_size){
    /* define coordinate transform function constants*/
    std::pair<unsigned, double> user = getUserInput();
    unsigned __CENTER_IDX = user.first;
    double __RADIUS = user.second;

    //offset such that (long, lat)(Cx, Cy) --> (Pix_x, Pix_y)(0, 0)
    double Cx = dataset[__CENTER_IDX]._x - __RADIUS, Cy = dataset[__CENTER_IDX]._y + __RADIUS;

    //x-scale factor such that ((Cx + 1) * Kx, Cy) --> (1, 0)
    double Kx = side_size / (2 * __RADIUS);

    //y-scale factor such that (Cx, (Cy - 1) * Ky) --> (0, 1)
    double Ky = -1 * side_size / (2 * __RADIUS);

    /* init PNG ret */
    cs225::PNG ret(side_size, side_size);

    /* parse dataset and load nodes to PNG */
    Node new_node;
    unsigned pix_x, pix_y, end_pix_x;
    double slope;
    for(auto node : dataset){
        /* color 3 by 3 pix square for each node */
        pix_x = std::floor((node._x - Cx) * Kx), pix_y = std::floor((node._y - Cy) * Ky);
        for(unsigned i = pix_x; i < pix_x + 3; i++){
            for(unsigned j = pix_y; j < pix_y + 3; j++){
                /* turn curr_pix to black */
                ret.getPixel(i, j).l = 0;
            }
        }

        /* color edges */
        for(auto edge : node._edges){
            /* get new_node */
            new_node = dataset[(node._idx == edge._start_node_idx) ? 
                edge._end_node_idx : edge._start_node_idx];
            
            /* get slope */
            slope = (new_node._y - node._y) / (new_node._x - node._x);

            /* parse new linear equation */
            pix_x = (node._x - Cx) * Kx, pix_y = (node._y - Cy) * Ky;
            end_pix_x = (new_node._x - Cx) * Kx;
            unsigned j;
            for(unsigned i = pix_x; i < end_pix_x; i++){
                /* calculate y_coordinate */
                j = (unsigned)(std::floor(slope * (i - pix_x) + pix_y));

                /* turn curr_pix to black */
                ret.getPixel(i, j).l = 0;
            }
        }
    }

    /* return */
    return ret;
}