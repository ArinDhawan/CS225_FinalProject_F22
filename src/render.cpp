#include "render.h"
#include "BFS.h"

/* render given dataset as PNG of dim side_size by side_size */
cs225::PNG render(std::vector<Node> dataset, std::vector<unsigned> short_path, unsigned side_size, unsigned res){
    /* define coordinate transform function constants*/
    std::pair<unsigned, double> user = getUserInput();
    unsigned __CENTER_IDX = user.first;
    double __RADIUS = user.second;

    /* get start idx */
    for(unsigned idx = 0; idx < dataset.size(); idx++){
        if(dataset[idx]._idx == __CENTER_IDX){
            __CENTER_IDX = idx;
        }
    }

    //offset such that (long, lat)(Cx, Cy) --> (Pix_x, Pix_y)(0, 0)
    double Cx = dataset[__CENTER_IDX]._x, Cy = dataset[__CENTER_IDX]._y;

    //offset of center pix of PNG
    double Px = side_size / 2, Py = side_size / 2;

    //x-scale factor such that ((Cx + 1) * Kx, Cy) --> (mid + 1, mid)
    double Kx = side_size / (2 * __RADIUS);

    //y-scale factor such that (Cx, (Cy + 1) * Ky) --> (mid - 1, mid)
    double Ky = side_size / (2 * __RADIUS);

    /* init PNG ret */
    cs225::PNG ret(side_size, side_size);

    /* init for following algo */
    Node new_node;
    unsigned new_node_idx, pix_x, pix_y, end_pix_x;
    double slope;
    bool colorFlag_1 = false, colorFlag_2 = false;

    /* pixel colors */
    cs225::HSLAPixel pix_grey(0, 0, 0.5, 1);
    cs225::HSLAPixel pix_black(0, 0, 0, 1);
    cs225::HSLAPixel pix_red(0, 1, 0.5, 0.4);
    cs225::HSLAPixel pix_green(147, 0.5, 0.5, 0.5);

    /* parse dataset and load nodes to PNG */
    for(auto node : dataset){
        /* set start_node color flag */
        for(auto short_idx : short_path){
            if(short_idx == node._idx){
                colorFlag_1 = true;
                break;
            }
        }

        /* color edges */
        for(auto edge : node._edges){
            /* get new_node */
            new_node_idx = (node._idx == edge._start_node_idx) ? edge._end_node_idx : edge._start_node_idx;
            for(unsigned idx = 0; idx < dataset.size(); idx++){
                /* match new_node to existing node in dataset */
                if(dataset[idx]._idx == new_node_idx){
                    new_node = dataset[idx];

                    /* set end_node color flag */
                    if(colorFlag_1){
                        for(auto short_idx : short_path){
                            if(short_idx == new_node._idx){
                                colorFlag_2 = true;
                                break;
                            }
                        }
                    }

                    /* get slope */
                    slope = (new_node._y - node._y) / (new_node._x - node._x);

                    /* parse linear equation */
                    pix_x = (node._x - Cx) * Kx + Px, pix_y = (node._y - Cy) * Ky + Py;
                    end_pix_x = (new_node._x - Cx) * Kx + Px;
                    unsigned j;
                    for(unsigned i = pix_x; i < end_pix_x; i++){
                        /* calculate y_coordinate */
                        j = (unsigned)(std::floor(slope * (i - pix_x) + pix_y));

                        /* color area */
                        for(unsigned r = i - 3 * res / 4; r < ret.width() && r < i + 3 * res / 4; r++){
                            for(unsigned c = j - 3 * res / 4; c < ret.height() && c < j + 3 * res / 4; c++){
                                /* turn curr_pix to color */
                                if(colorFlag_1 && colorFlag_2){
                                    ret.getPixel(r, c) = pix_green;
                                }
                                else{
                                    ret.getPixel(r, c) = pix_grey;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            colorFlag_2 = false;
        }

        /* color pix square for each node */
        pix_x = std::floor((node._x - Cx) * Kx + Px), pix_y = std::floor((node._y - Cy) * Ky + Py);

        /* color n by n area */
        for(unsigned i = pix_x - res; i >= 0 && i < ret.width() && i < pix_x + res; i++){
            for(unsigned j = pix_y - res; j >= 0 && j < ret.height() && j < pix_y + res; j++){
                /* turn curr_pix to color */
                if(colorFlag_1){
                    ret.getPixel(i, j) = pix_red;
                }
                else{
                    ret.getPixel(i, j) = pix_black;
                }
            }
        }
        colorFlag_1 = false;
    }

    /* return */
    return ret;
}