#pragma once

#ifndef RENDER_H
#define RENDER_H

#include "Node.h"
#include "../lib/cs225/PNG.h"
#include "../src/dijkstra.h"



/* render given dataset as PNG of dim side_size by side_size */
cs225::PNG render(std::vector<Node> dataset, Dijkstra path, unsigned destination_idx, unsigned side_size, unsigned res);

#endif