#include "render.h"
#include "BFS.h"

/* render given dataset as PNG of dim side_size by side_size */
cs225::PNG render(std::vector<Node> dataset, unsigned side_size, unsigned res){
    /* define coordinate transform function constants*/
    std::pair<unsigned, double> user = getUserInput();
    unsigned __CENTER_IDX = user.first;
    double __RADIUS = user.second;

    //get start index
    for(auto node : dataset){
        if(node._idx == __CENTER_IDX){
            __CENTER_IDX = node._idx;
            break;
        }
    }

    //offset such that (long, lat)(Cx, Cy) --> (Pix_x, Pix_y)(0, 0)
    double Cx = dataset[__CENTER_IDX]._x, Cy = dataset[__CENTER_IDX]._y;

    //offset of center pix of PNG
    double Px = side_size / 2, Py = side_size / 2;

    //x-scale factor such that ((Cx + 1) * Kx, Cy) --> (1, 0)
    double Kx = side_size / (2 * __RADIUS);

    //y-scale factor such that (Cx, (Cy - 1) * Ky) --> (0, 1)
    double Ky = side_size / (2 * __RADIUS);

    /* init PNG ret */
    cs225::PNG ret(side_size, side_size);

    /* parse dataset and load nodes to PNG */
    Node new_node;
    unsigned new_node_idx;
    unsigned pix_x, pix_y, end_pix_x;
    double slope;
    for(auto node : dataset){
        /* color edges */
        for(auto edge : node._edges){
            /* get new_node */
            new_node_idx = (node._idx == edge._start_node_idx) ? edge._end_node_idx : edge._start_node_idx;
            for(auto n_node : dataset){
                /* match new_node to existing node in dataset */
                if(n_node._idx == new_node_idx){
                    new_node = dataset[new_node_idx];

                    /* get slope */
                    slope = (new_node._y - node._y) / (new_node._x - node._x);

                    /* parse new linear equation */
                    pix_x = (node._x - Cx) * Kx + Px, pix_y = (node._y - Cy) * Ky + Py;
                    end_pix_x = (new_node._x - Cx) * Kx + Px;
                    unsigned j;
                    for(unsigned i = pix_x; i < end_pix_x; i++){
                        /* calculate y_coordinate */
                        j = (unsigned)(std::floor(slope * (i - pix_x) + pix_y));

                        /* color n by n area */
                        for(unsigned r = i - res / 2; r < ret.width() && r < i + res / 2; r++){
                            for(unsigned c = j - res / 2; c < ret.height() && c < j + res / 2; c++){
                                /* turn curr_pix to red */
                                cs225::HSLAPixel & pix = ret.getPixel(r, c);
                                pix.h = 0;
                                pix.l = 0.5;
                                pix.s = 1;
                            }
                        }
                    }
                    break;
                }
            }
        }

        /* color pix square for each node */
        pix_x = std::floor((node._x - Cx) * Kx + Px), pix_y = std::floor((node._y - Cy) * Ky + Py);

        /* color n by n area */
        for(unsigned i = pix_x - res; i >= 0 && i < ret.width() && i < pix_x + res; i++){
            for(unsigned j = pix_y - res; j >= 0 && j < ret.height() && j < pix_y + res; j++){
                /* turn curr_pix to black */
                cs225::HSLAPixel & pix = ret.getPixel(i, j);
                pix.l = 0;
            }
        }
    }

    /* return */
    return ret;
}