/*
	Assignment 3 - Single Destination Shortest Path Problem
	James Dorevski
	jd107
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define ROOT 1
#define VERTEX_HEAP_SIZE verticesQueue[0]
#define NO_EDGE 0

struct Vertex {
	bool visited;
	char label;
	int x, y, distance, parentVertex, heapPosition;
	double heuristic;
};

// stores path data found by dijkstra's 
struct Path { 
	int *vertices;
	int edgeCount, length;
};

// global variables
int numberOfVertices, numberOfEdges, verticesVisited = 0;
char startingVertex, goalVertex;
int stackIndex = -1;

// data structures
int **adjacencyMatrix; // holds the edges 
Vertex *vertices;
int *shortestPathStack; // stack to store vertices on the shortest path 

// min-heap based on vertex distance and heuristic
class VertexDistanceQueue {
private:
	int *verticesQueue; // points to vertices in the vertices array

public:
	VertexDistanceQueue();
	~VertexDistanceQueue() { delete[] verticesQueue; }

	void insertNode(int index);
	void siftNodeUp(int currentNode);
	void siftNodeDown(int currentNode);
	void swapNode(int &x, int &y);
	int removeRoot();
	bool isEmpty() { return VERTEX_HEAP_SIZE == 0; }
	int getSize() { return VERTEX_HEAP_SIZE; }
	void reset() { VERTEX_HEAP_SIZE = 0; }
};

VertexDistanceQueue::VertexDistanceQueue() {
	verticesQueue = new int[numberOfVertices + 1]; 
	VERTEX_HEAP_SIZE = 0;
}

void VertexDistanceQueue::insertNode(int index) { 
	if (VERTEX_HEAP_SIZE >= numberOfVertices + 1) {
		cerr << "Heap is full." << endl;
		exit(3);
	}

	verticesQueue[++VERTEX_HEAP_SIZE] = index;
	vertices[index].heapPosition = VERTEX_HEAP_SIZE; // saves the position of the vertex in the heap so we can easily siftUp the node that dijkstra's is checking 
	siftNodeUp(VERTEX_HEAP_SIZE);
}

void VertexDistanceQueue::siftNodeUp(int currentNode) {
	if (currentNode == ROOT) {
		return;
	}

	int parentNode = currentNode / 2;

	if (vertices[verticesQueue[parentNode]].distance + vertices[verticesQueue[parentNode]].heuristic < vertices[verticesQueue[currentNode]].distance + vertices[verticesQueue[currentNode]].heuristic) {
		return;
	} else {
		swapNode(verticesQueue[currentNode], verticesQueue[parentNode]);
		siftNodeUp(parentNode);
	}
}

void VertexDistanceQueue::siftNodeDown(int currentNode) {
	int bestChild = currentNode * 2;

	if (bestChild > VERTEX_HEAP_SIZE) {
		return;
	}

	if ((bestChild + 1) <= VERTEX_HEAP_SIZE) {
		if (vertices[verticesQueue[bestChild + 1]].distance + vertices[verticesQueue[bestChild + 1]].heuristic < vertices[verticesQueue[bestChild]].distance + vertices[verticesQueue[bestChild]].heuristic) {
			bestChild++;
		} 
	}

	if (vertices[verticesQueue[bestChild]].distance + vertices[verticesQueue[bestChild]].heuristic < vertices[verticesQueue[currentNode]].distance + vertices[verticesQueue[currentNode]].heuristic) {
		swapNode(verticesQueue[currentNode], verticesQueue[bestChild]);
		siftNodeDown(bestChild);
	}
}

int VertexDistanceQueue::removeRoot() {
	if (VERTEX_HEAP_SIZE == 0) {
		cerr << "Heap is empty therefore cannot remove anything. You're not supposed to see this." << endl;
		exit(4);
	}

	// root is 1
	int v = verticesQueue[ROOT];
	swapNode(verticesQueue[1], verticesQueue[VERTEX_HEAP_SIZE]);
	VERTEX_HEAP_SIZE--;
	siftNodeDown(ROOT);

	return v;
}

void VertexDistanceQueue::swapNode(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp;

	// also updates the heap position on the swapped nodes
	int tempPosition = vertices[x].heapPosition;
	vertices[x].heapPosition = vertices[y].heapPosition;
	vertices[y].heapPosition = tempPosition;
}


// stack utlity function
void push(int vertex) {
	if (stackIndex == numberOfVertices - 1) { // -1 because stackIndex starts at -1
		cerr << "Stack is full." << endl;
	} else {
		shortestPathStack[++stackIndex] = vertex;
	}
}

void readGraphSize(ifstream &in) {
	if (!in.good()) {
		cerr << "ass3.txt could not be opened or found. Exiting program." << endl;
		exit(1); 
	}

	in >> numberOfVertices >> numberOfEdges;

	// checks if the number of vertices and edges read in is smaller that the smallest possible graph
	if (numberOfVertices < 2 || numberOfEdges < 1) { 
		cerr << "An invalid number of vertices or edges were read in. Exiting program." << endl;
		exit(2);
	}
}

void readVerticesAndEdges(ifstream &in) {
	char start, end;
	int weight;
	Vertex currentVertex;

	for (int i = 0; i < numberOfVertices; i++) {
		in >> currentVertex.label >> currentVertex.x >> currentVertex.y;
		currentVertex.distance = INT_MAX; // initialise all distances to the max int size
		currentVertex.heuristic = 0; // for A*
		currentVertex.visited = false;
		currentVertex.parentVertex = -1; // -1 = source vertex
		vertices[i] = currentVertex;
	}

	// reads the edges into a directed graph stored in the adjacency matrix
	for (int i = 0; i < numberOfEdges; i++) {
		in >> start >> end >> weight;
		adjacencyMatrix[start - 'a'][end - 'a'] = weight; 
	}

	// reading in the start and goal vertex once everything else has been set up
	in >> startingVertex >> goalVertex;
	in.close(); // finally close the ifstream 
}

// used in part 1 but not needed anymore
void displayMatrix() {
	for (int i = 0; i < 5; i++) {
		cout << (char)(i + 'a') << ": "; // need to re-add 'a' to display correct char

		for (int j = 0; j < numberOfVertices; j++) {
			// exclude empty parts of matrix
			if (adjacencyMatrix[i][j] < 1) {
				continue;
			}
			cout << (char)(j + 'a') << "(" << adjacencyMatrix[i][j] << ") ";
		}
		cout << endl;
	}
}

// pushes the edges along the shortest path onto the stack
void getshortestPathStack(int currentVertex) {
	if (vertices[currentVertex].parentVertex == -1) { // if stack is empty
		push(currentVertex);
		return;
	} else if (vertices[currentVertex].parentVertex > -1){
		push(currentVertex);
		getshortestPathStack(vertices[currentVertex].parentVertex);
	}
} 

void displayPathInfo(Path path) {
	if (path.edgeCount >= 0) {
		cout << "Path: ";
		for (int i = 0; i <= path.edgeCount; i++) {
			cout << (char)(path.vertices[i] + 'a') << " ";
		}
	}
	cout << endl;
	cout << "Path distance: " << path.length << endl;
	cout << "Number of vertices visited: " << verticesVisited << endl;

	verticesVisited = 0;
}

Path dikjstraShortestPath(VertexDistanceQueue &verticesQueue) {
	verticesQueue.insertNode(startingVertex - 'a'); // add the source vertex to the heap 
	vertices[startingVertex - 'a'].distance = 0; //distance from source is always 0

	int currentVertex;
	while (!verticesQueue.isEmpty()) {
		currentVertex = verticesQueue.removeRoot();
		vertices[currentVertex].visited = true;
		verticesVisited++;

		if (currentVertex == goalVertex - 'a') { // break the loop once we've found our target
			break;
		}

		for (int i = 0; i < numberOfVertices; i++) {
			if (adjacencyMatrix[currentVertex][i] > NO_EDGE && !vertices[i].visited) { // check if an edge exists and if the vertex hasn't been visited before 
				if (vertices[i].distance == INT_MAX) { 
					vertices[i].distance = vertices[currentVertex].distance + adjacencyMatrix[currentVertex][i];
					vertices[i].parentVertex = currentVertex;
					verticesQueue.insertNode(i);
				} else { // update the distance if the new distance is less than the current distance
					int newDistance = vertices[currentVertex].distance + adjacencyMatrix[currentVertex][i];
					if (newDistance < vertices[i].distance) { 
						vertices[i].distance = newDistance;
						vertices[i].parentVertex = currentVertex;

						verticesQueue.siftNodeUp(vertices[i].heapPosition); // sift the updated vertex back on the min-heap with O(1) lookup thanks to saving the position
					}
				}
			}
		}
	}

	Path foundPath; // stores information about the path found by dijkstra's 
	foundPath.length = 0; // to fix the int being set as random memory garbage so the check if goal vertex wasn't reached works correctly

	// protect if goal vertex could not be found
	if (currentVertex != goalVertex - 'a') {
		return foundPath;
	}

	getshortestPathStack(currentVertex);

	foundPath.vertices = new int[stackIndex + 1]; // plus 1 as stackIndex starts at -1
	
	int j = 0;
	for (int i = stackIndex; i >= 0; i--) {
		foundPath.vertices[j++] = shortestPathStack[i]; // populates foundPath with the vertices along the shortest path 
	}
	foundPath.edgeCount = stackIndex;
	foundPath.length = vertices[goalVertex - 'a'].distance;
	return foundPath;
}

// resets vertices so dijkstra's can be run again 
void resetVertices(VertexDistanceQueue &verticesQueue) {
	verticesQueue.reset();
	stackIndex = -1;

	for (int i = 0; i < numberOfVertices; i++) {
		vertices[i].distance = INT_MAX;
		vertices[i].visited = false;
		vertices[i].parentVertex = -1;
	}
}

Path dikjstraSecondShortestPath(VertexDistanceQueue &verticesQueue, Path shortestPath) {
	Path secondShortestPath;
	secondShortestPath.length = INT_MAX;
	secondShortestPath.vertices = new int[1]; // temp to prevent bad memory stuff from happening on the first run (if there is no memory allocated and the for loop tries to deallocate)
 	
 	// goes through the edges on the shortest path and re-runs dijkstra's with one removed 
	for (int i = 0; i < shortestPath.edgeCount; i++) {
		int tempWeight = adjacencyMatrix[shortestPath.vertices[i]][shortestPath.vertices[i + 1]];
		adjacencyMatrix[shortestPath.vertices[i]][shortestPath.vertices[i + 1]] = NO_EDGE; // exclude it from the graph  
		resetVertices(verticesQueue);	
		Path candidate = dikjstraShortestPath(verticesQueue);
		
		if (stackIndex == -1) { // if there is nothing in the stack then there is nothing in the path
			continue;
		}

		adjacencyMatrix[shortestPath.vertices[i]][shortestPath.vertices[i + 1]] = tempWeight; // re-add the edge that was taken out 

		// check if the candidate path is shorter and free up the memory of the longer path 
		if (candidate.length < secondShortestPath.length && candidate.length > shortestPath.length) { // makes sure that the second shortest path is longer than the shortest path
			delete [] secondShortestPath.vertices;
			secondShortestPath = candidate; // shortestPath gets set to the new candidate returned if it's shorter that the current candidate 
		} else {
			delete [] candidate.vertices; // if the possible candidate is longer remove it from memory 
		}
	}

	return secondShortestPath;
}

// calculates euclidean distance as a heuristic for the vertices 
double euclideanDistance(double goalX, double goalY, double x, double y) {
	double euclideanDist = pow(goalX - x, 2) + pow(goalY - y, 2);
	return sqrt(euclideanDist);
}

void setHeuristic(int i) {
	double goalX = vertices[goalVertex - 'a'].x;
	double goalY = vertices[goalVertex - 'a'].y;

	double x = vertices[i].x;
	double y = vertices[i].y;

	vertices[i].heuristic = euclideanDistance(goalX, goalY, x, y);
}

// resets the vertices and sets the heuristics for each vertex so A* algorithm can work 
void aStarRefresh(VertexDistanceQueue &verticesQueue) {
	verticesQueue.reset();
	stackIndex = -1;

	for (int i = 0; i < numberOfVertices; i++) {
		vertices[i].distance = INT_MAX;
		vertices[i].visited = false;
		vertices[i].parentVertex = -1;
		setHeuristic(i);
	}
} 

// if the found path's length is 0 it means no shortest path was found to the goal vertex as per the logic in dijkstra's
void checkPathExistanceShortest(Path &path) {
	if (path.length == 0) {
		cerr << "No path was found between the start and goal vertex. Exiting program." << endl;
		exit(8);
	}
}

// checks if the returned path's length is INT_MAX which would be the case if dijkstra's could not find a second shortest path 
void checkPathExistanceSecondShortest(Path &path) {
	if (path.length == INT_MAX) {
		cerr << "No path was found between the start and goal vertex. Exiting program." << endl;
		exit(8);
	}
}

int main() {
	ifstream in("ass3.txt");

	// step 1
	readGraphSize(in);
	// initialise arrays now that we know the number of vertices 
	vertices = new Vertex[numberOfVertices]; 
	shortestPathStack = new int[numberOfVertices];

	// setting up array of arrays 
	adjacencyMatrix = new int*[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) {
		adjacencyMatrix[i] = new int[numberOfVertices];
	}

	readVerticesAndEdges(in);

	cout << "Start and end vertex: " << startingVertex << " " << goalVertex << endl;

	// step 2
	cout << endl << "--- Finding Shortest Path Using Dijkstra's ---" << endl;
	VertexDistanceQueue verticesQueue;
	Path shortestPath = dikjstraShortestPath(verticesQueue);
	checkPathExistanceShortest(shortestPath);
	displayPathInfo(shortestPath);

	// step 3
	cout << endl << "--- Finding Second Shortest Path Using Dijkstra's ---" << endl;
	Path secondShortestPath = dikjstraSecondShortestPath(verticesQueue, shortestPath);
	checkPathExistanceSecondShortest(secondShortestPath);
	displayPathInfo(secondShortestPath);

	// refreshing for A*
	aStarRefresh(verticesQueue);

	// step 4	
	cout << endl << "--- Finding Shortest Path Using A* algorithm ---" << endl;
	Path aStarShortestPath = dikjstraShortestPath(verticesQueue);
	checkPathExistanceShortest(aStarShortestPath);
	displayPathInfo(aStarShortestPath);
	
	cout << endl << "--- Finding Second Shortest Path Using A* algorithm ---" << endl;
	Path aStarSecondShortestPath = dikjstraSecondShortestPath(verticesQueue, aStarShortestPath);
	checkPathExistanceSecondShortest(aStarSecondShortestPath);
	displayPathInfo(aStarSecondShortestPath);

	// clearing memory 
	delete [] vertices;
	delete [] shortestPathStack;
	delete [] shortestPath.vertices;
	delete [] secondShortestPath.vertices;
	delete [] aStarShortestPath.vertices;
	delete [] aStarSecondShortestPath.vertices;

	for (int i = 0; i < numberOfVertices; i++) {
		delete [] adjacencyMatrix[i];
	}
	delete [] adjacencyMatrix;

	return 0;
}


/*
	QUESTIONS:
	- What if we require the second shortest path be longer than the shortest path?
		I have implemented a check that compares whether a possible second shortest path candidate is longer than  
		the shortestPath length to ensure that the second path is longer. 
	- What if the graph contains cycles?
		My implementation of Dijkstra's will never contain cycles because it keeps track of which vertices it has already visited. 
		However, negative cycles can potentially cause infinite loops for some pathfinding algorithms. 
	- What if the graph is undirected?
		Dijkstra's works on both a directed and undirected graph. To make it an undirected graph when your inserting the edges
		into the adjacency matrix you just also insert the reverse order of the labels with the same weight given.
	
	ALGORITHMS USED:
	- Dijkstra's algorithm -- Using Dijkstra's algorithm allows us to calculate the shortest path between two nodes in a graph. It was used 
	with a heuristic of 0. 
	- Second shortest path -- To find the second shortest path we remove an edge from the found shortest path, then run dijkstra's again to 
	find the shortest path of the graph with that edge removed. We then re-add that edge and set the length of the secondShortestPath object to the length. 
	After that we remove the next edge in the shortest path and run dijkstra's again, and compare that candidate path with the secondShortestPath length.
	We repeat this over every edge in the shortest path then once all the edges in the shortest path have been iterated over in that manner we are left 
	with the second shortest path. 
	- A* -- Using an heuristic with dijkstra's helps guide the A* algorithm into determining the minimum cost from any vertex to the goal, 
	allowing it to get to the goal vertex without searching as many vertices. The euclidean distance was chosen as a heuristic.  
	
	DATA STRUCTURES USED:
	- Adjacency matrix -- O(1) lookup if edge exists, performance is worse over an adjacency list for getting an outgoing vertex.
		// adjacency list is better if graph is sparse, matrix is better if your graph is dense.
	- Min-heap -- O(1) lookup to find which is the next best node to explore. 
	- Stack -- Used to store the parent nodes. It goes through the parents to generate the path. A stack was used because it's FILO. 

	FURTHER OPTIMISATIONS:
	- The min-heap was further optimised by saving each vertices location in the heap for when dijkstra's updates a candidate vertex in the heap, 
	you know where the node is so you straight away sift up on that node. Optimises from O(n) lookup to O(1).
	- Using a visited boolean and saving the distance within the Vertex struct saved me from using a seperate array to store that information.
	- Measures were provided to handle if Dijkstra's algorithm could not find a path to the goal vertex in the graph provided. 
*/
