#include "Node.h"
#include "../lib/cs225/PNG.h"

#pragma once

/* render given dataset as PNG of dim side_size by side_size */
cs225::PNG render(std::vector<Node> dataset, unsigned side_size);