## Leading Question 
As athletes, we find ourselves wanting a way to find a new running or biking path, especially if we have a target distance, like a 5k or half-marathon. Unfortunately, there isn’t a convenient method to plot a path without analyzing a map by hand. Our end goal is to produce a search tool capable of calculating a path as close as possible to a target distance, given a start and end point.

We plan on doing this by taking Utah’s Road Networks and Points of Interest dataset. This is easily the most convenient dataset out of those provided, primarily because of its storage of nodes (giving longitude and latitude), and the corresponding edges between them (storing start point, end point, and distance). The actual algorithms behind this are described below, but the general idea is to follow a similar algorithm to “shortest path”, but instead implement a path that’s closest to our target distance (5k, half-marathon, 2 miles, etc). 

One of the problems we face with this dataset is its sheer size. Each set has about 21,000 nodes, and even more connections between them. To handle this, we plan on sectioning off chunks of data within a certain radius between the start and end points, so as to not traverse the entire set (Ex: we don’t want to traverse all of California if we want to run a 5k in LA). More of this compression of the dataset can be seen under the Data Correction section.

https://www.cs.utah.edu/~lifeifei/research/tpq/cal.cnode

https://www.cs.utah.edu/~lifeifei/research/tpq/cal.cedge

### Dataset Acquisition and Processing
We will be using Utah’s Road Networks and Points of Interest database for this project. More specifically, the California Road Network’s Nodes & Edges.
## Data Format
The data in California Road Network's Nodes is formatted as the node identifier along with its longitude and latitude coordinate per row. It contains 21,692 rows of data. The data in California Road Netwrok's Edges is formatted as edge identification, starting node, ending node, and distance between the nodes per row. It contains 21,047 data points. We will only be using a subset of this dataset which will be defined by the area of a circle overlaid on a map of California. If nodes and edges correspond to a point within the circle then it will be included in the subset of the dataset.

## Data Correction
The first step to verify that our circle-region subset of the California road network is correct is to check for incorrect nodes. Meaning, a test will be run to identify any node included in the subset that exceeds the radius/distance from the longitude-latitude center of the circle-region. Secondly, to identify any node that should be included in the subset and is missing, we will identify all nodes in the data set within the radius/distance from the longitude-latitude center of the circle-region. Then we will verify that there exists a path from each identified node to either the start or end nodes over the newly created subset of identified nodes. Nodes that pass all these tests will be counted and compared to the number of nodes in the original make-circle-subset function.

## Data Storage

We’ll need a couple preprocessed data vectors for storing valid data points and edges from the raw data. We’ll iterate through the given node data, and determine whether a node is valid or not based on its distance from the “center point” between our start and end node (our determined radius). The raw data stores nodes as numbers (0, 1 2). Once we determine which nodes are valid, we can iterate through the edge dataset (which provides starting and ending points). We’ll only add these edges if it meets these conditions: 1. It starts at a valid node, and 2. It ends at a valid node. In total, we’ll have to preprocessed data vectors:
Valid node vector (storing nodes within the target radius)
Valid edge vector (storing the corresponding edges that we can walk on)


We will have a vector of Node Objects. These Node Objects will hold an X-coordinate representing the node’s longitude, an Y-coordinate for latitude, and a vector of Edge Class Objects representing the streets starting at this node. These Edge Objects will hold a pointer to the next Node Object and the weight (distance) to the next Node. Iterating through this will behave like a tree, with its “children” being the nodes at the end of the edges. 

We will be using a vector to store the final route.

Total Storage Cost in Big O Notation: O(E + V), E → Edges, V → Nodes/ Vertices
### Algorithm 
##Function Inputs
The input values of our function will be the longitude and latitude coordinates to define the center of our circle along with the radius of the circle. We would also input the starting and ending node longitude and latitude.
##Function Outputs
The function would output a PNG file of all the nodes in the given circle and then highlight the path of interest. Nodes of non-interest will be black while nodes of interest will be assigned a bright color to help trace out the path. Different pathways may be layered above each other depending on how many times the function is run.
##Function Efficiency

Graph Traversal: BFS → to make the circle subset → SPEED O(E + V), E → Edges, V → Nodes/ Vertices : MEMORY O(1) DOES NOT CREATE NEW MEMORY
Graph Data Algorithm 1: Dijkstra's Algorithm → Shortest path algorithm → SPEED O(E + V * log(V)) : MEMORY O(1) DOES NOT CREATE NEW MEMORY
Graph Data Algorithm 2: Closest path to target distance algorithm → SPEED O((E + V * log(V))(E + V) : DOES NOT CREATE NEW MEMORY
### Timeline
Important deliverable deadlines:

Nov 13th, 2022 - With two selected points find a circle region encompassing the dataset and creating a subset for the dataset and forming a graph from that  subset of nodes

Nov 18th, 2022 - Implementing the shortest path algorithm on the dataset

Nov 27th, 2022 -  Finding the shortest shortest distance closest to target distance we want to achieve

Dec 5th , 2022 - Render the shortest path onto a PNG

Dec 7th, 2022 - Finish and complete the deliverables for the project
