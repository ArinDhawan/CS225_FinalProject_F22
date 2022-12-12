#pragma once

#ifndef RENDER_H
#define RENDER_H

#include "Node.h"
#include "../lib/cs225/PNG.h"



/* render given dataset as PNG of dim side_size by side_size */
cs225::PNG render(std::vector<Node> dataset, std::vector<unsigned> short_path, unsigned side_size, unsigned res);

#endif