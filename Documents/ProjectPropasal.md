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
Our data formulation & correction will occur in 2 main sections. First step will be taking in valid nodes from the given dataset. A valid node is one that fits within a predetermined radius of the starting node (at least the distance between the start and end nodes). As we parse through the dataset, we’ll only add nodes that fall within this given radius (based on the longitude & latitude locations of said nodes compared to the start node). If a node is within the radius, it will be added to our adjacency list, along with its valid adjacent edges. The in-depth description of this dataset is in the next section.

The second step primarily involves the development process. While we’ll primarily be using A* as our path algorithm, we’ll be falling back on Dijsktra’s Algorithm to validate our findings. We’ll run both programs on the same dataset, with the same start and end points, and compare the total distance traveled by each algorithm. We assume Dijsktra’s algorithm will be more accurate, primarily due to its more reliable search method, which is why we’ll be comparing against it. Based on our results, we’ll tweak our A* algorithm to best match the results of Dijsktra’s. This may involve anything from changing the handling of input data, to our data structures, to basic calculations within our code. 
## Data Storage
Our sole Data Storage throughout this project is our stored center Node coordinates and generated adjacency lists of Node pointers representing the ‘circle’ subset carved from the roads database. This adjacency list is a 1-D vector of linked lists. The index of the vector represents the corresponding Node number (given in BFS order with 0th index being the center Node). The value stored in each index is the head node which contains the latitude (x) and longitude (y) coordinates of the i-th Node and holds a pointer to the first of its adjacent Nodes.

Total Storage Cost: 𝑂(|V| + |E|)
### Algorithm 
The primary algorithm we’ll be using is the A* algorithm, which builds upon Dijkstra's Algorithm. As stated in the A* wiki, A* can be used to find the shortest path between 2 points within a given sphere (or in our case, a circle) around the starting point. This generates the shortest path based on informed weights (distances between 2 nodes). A* has a faster runtime than the base Dijkstra, but its greedy nature may make it vulnerable to inaccuracies. To account for this, we’ll also be implementing the basic Dijkstra Algorithm. 
	The basic Dijkstra Algorithm can be implemented relatively easily, and can serve as a validation tool for the rest of our project. We’ll compare the results of A* against this algorithm, and make adjustments where necessary to improve accuracy.
	Once we get our “shortest path” algorithms working, we’ll be able to implement our more difficult goals, such as meeting a target distance (5k, marathon, 10 miles, etc). 
##Function Inputs

BFS Function Input – Create subset (adjacency list) from dataset: California Roads dataset, Node * center, and double radius. Dataset is a list of Nodes with longitude and latitude coordinates and Edges with starting and ending Nodes as well as distance between Nodes. Center is a user-selected node to act as the center point of the to-be generated ‘circle’ subset of Nodes. Radius is the maximum allowed longitude-latitude distance between the center Node and a Node appended to the subset.

A* Algorithm – Main Shortest Path Algo: ‘Circle’ subset of California Roads dataset and start and goal Nodes.

Dijkstra’s Algorithm – Error Correction Shortest Path Algo: same as A*. ‘Circle’ subset of California Roads dataset and start and goal Nodes.
Render Image Function: Takes adjacency list and Node path from either the previous A* or Dijkstra’s Algorithm.

##Function Output
BFS Function Output: Adjacency List of ‘Circle’ subset

A* Algorithm: Node path from start node to goal node.

Dijkstra’s Algorithm: Node path from start node to goal node.

Render Image Function: PNG of ‘Circle’ subset with the the shortest path superimposed on the image.
##Function Efficiency

BFS: Time and Space Complexity for adjacency list is 𝑂(|V| + |E|), where V is the no of vertices and E is the no of edges.

Dijkstra's Algorithm: The runtime for list representation would be 𝑂(Elog(V)). And the space complexity for the adjacency list representation for the graph would be 𝑂(V2), (v being the number of vertices).

A* Search algorithm :  The space complexity of A* depends on the heuristic. In the worst case of an unbounded search space, the number of nodes expanded is exponential in the depth of the solution (the shortest path) d: 𝑂(bd), where 𝑏 is the branching factor (the average number of successors per state). For our graph traversal, the best run-time would be  𝑂(|V| + |E|). For its worst case, it would reduce itself to Dijkstra's algorithm.

Render Image Function: Runtime will be the same as BFS, which is 𝑂(|V| + |E|). Space complexity will be 𝑂(V^2), as the worst case scenario for the given shortest path is that it traverses over all nodes in the adjacency list.
### Timeline
Important deliverable deadlines:

Nov 13th, 2022 - With two selected points find a circle region encompassing the dataset and creating a subset for the dataset and forming a graph from that  subset of nodes

Nov 18th, 2022 - Implementing the shortest path algorithm on the dataset


Nov 27th, 2022 -  Finding the shortest shortest distance closest to target distance we want to achieve

Dec 5th , 2022 - Render the shortest path onto a PNG

Dec 7th, 2022 - Finish and complete the deliverables for the project
