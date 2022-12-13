# **CS 225 Final Project Result Report Fall 2022**
**Team members:** Noah Breit, Peter Giannetos, Ben Olaivar, Arin Dhawan  
**Group Name:** HeyBeter




 # **Algorithms Developed** 

*Here is an overview of the algorithms we developed.*

## BFS(Breath-First Search)

Description:


Using our Breadth-First Search algorithm traversal, we are going to convert our dataset into an adjacency list (in the form of a std::vector). We achieved this by:

1. Getting the user’s input for the center node and the radius(distance they want to cover)
2. Creating a dataset of nodes(std:vector) from nodes and edges file
3. Then, we make a subset of the given database according to the user in
4. Making an edge and node set(std::vector) using the given files
5. Then, we make an adjacent set which combines the nodes and edges sets to make a set of nodes with their adjacent edges. 


Output:


OUTPUTS: vector node dataset of combine nodes and edges

std::vector<Node> makeDataSet(std::string file_name_node, std::string file_name_edge);
 
OUTPUT: combined vector list of nodes with edges per node

std::vector<Node> makeAdjSet(std::vector<Node> nodeSet, std::vector<Edge> edgeSet);
 

OUTPUTS: subset of a vector list of nodes with edges per node

std::pair<unsigned, double> makeSubset(std::vector<Node>& subset, std::vector<Node> dataset);



## Dijkstra's Algorithm


Description:


For our smaller dataset :

0 -121.904167 41.974556

1 -121.902153 41.974766

2 -121.896790 41.988075

3 -121.889603 41.998032

4 -121.886681 42.008739

5 -121.915062 41.970314

6 -121.910088 41.973942

7 -121.916199 41.969482

8 -121.903198 41.968456

The steps for this process are as follows (follow ):
1. Mark current node as visited
2. The visited status of a node is kept in the nodes_visited_ vector
3. Add all the edges from the current node to the edges_
edges_ keeps track of all the available edges to traverse for the next step. This ensures the “shortest edge” is only from a node we’ve visited
4. Find the shortest edge from the edges_ vector
5. Follow the shortest edge and update the current node
6. If the distance from the previous node is shorter than that node’s current distance, then update it’s current distance. Also update it’s “previous” part in the ‘path’ vector. 
7. Repeat steps 1-4 until all edges have been visited



	As mentioned earlier, each node has a corresponding pair, with the first part being its node ID, and the second part being the ID of the ‘previous’ node (as indicated by the red arrows in Figure 7). A node only needs to know the closest edge, and its total distance from the start node. This means we are calculating the distance from the start to each node. These distances are stored in the corresponding distances_ vector index. To get the path from a certain node, we traverse the “previous” node until we reach our starting node (again, the distances are measured with respect to the starting node).

Output:

The output of this function is a vector<unsigned> path in starting-ending order. For example, if we wanted the path from node ‘0’ to node ‘7’, the path returned would be stored as [0,6,5,7].


## Render PNG

Description: Takes in an Adjacency Matrix of Nodes and Edges, as well as an Dijkstra Class Object to solve the shortest path problem and a destination node idx and parameters to handle the sizing and resolution of the outputted PNG file.

Output: A PNG with the shortest path from one node to the other.






 

