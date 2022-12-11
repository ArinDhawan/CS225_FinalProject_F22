#pragma once

#ifndef RENDER_H
#define RENDER_H

#include "Node.h"
#include "../lib/cs225/PNG.cpp"



/* render given dataset as PNG of dim side_size by side_size */
cs225::PNG render(std::vector<Node> dataset, unsigned side_size);

#endif