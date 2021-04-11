#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
#include<future>
#define INF INT_MAX
using namespace std;

struct Graph {
	int V; // count of the nodes in the graph
	vector<int>* adjList; // neighbors
};

//fucntions:
void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& dist);
void addEdge(Graph* graph, int src, int dest);
Graph* build_random_graph(int V, float p);
int diameter(Graph* graph);
bool Is_Isolated(Graph* graph);
bool connectivity(Graph* graph);
int Test1(int V, int itr, float P);
int Test2(int V, int itr, float P);
void test2Loop(int start, int end, int V, float P, vector<int>* counter, int itr);
int Test3(int V, int itr, float P);


// A utility function that creates a graph of V vertices
Graph* createGraph(int V) {
	Graph* graph = new Graph;
	graph->V = V;

	// Create an array of sets representing
	// adjacency lists.  Size of the array will be V
	graph->adjList = new vector<int>[V];

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
	// Add an edge from src to dest.  A new
	// element is inserted to the adjacent
	// list of src.
	graph->adjList[src].push_back(dest);

	// Since graph is undirected, add an edge
	// from dest to src also
	graph->adjList[dest].push_back(src);
}


Graph* build_random_graph(int V, float P) {
	Graph* graph;
	graph = createGraph(V);
	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++) {
			float r = ((float)rand() / (RAND_MAX)); //rolls "random" theta
			if (r <= P)
				addEdge(graph, i, j);
		}
	}
	return graph;
}

int diameter(Graph* graph) {

	int diameter = 0;
	//for each vertex in the graph 
	for (int i = 0; i < graph->V; i++) {
		vector<bool> visited(graph->V, false);
		vector<int> distance(graph->V, INF);
		// initialising the start vertex
		visited[i] = true;
		distance[i] = 0;
		BFS(graph, i, visited, distance);
		// distance from the start vertex to the farthest leaf
		int max_dist = *max_element(distance.begin(), distance.end());
		if (max_dist == INF)
			return INF;
		if (diameter < max_dist)
			diameter = max_dist;
	}
	return diameter;
}

bool Is_Isolated(Graph* graph) {

	for (int i = 0; i < graph->V; i++) {
		// check if the "i" node has neighbors
		if (graph->adjList[i].empty())
			return true;
	}
	return false;
}

bool connectivity(Graph* graph) {
	vector<bool> visited(graph->V, false);
	vector<int> distance(graph->V, INF);
	// initialising the start vertex
	visited[0] = true;
	distance[0] = 0;
	BFS(graph, 0, visited, distance);
	//stating from the second vertex
	for (int i = 1; i < graph->V; i++) {
		if (!visited[i]) // if not visited that means BFS fucntion hasn't reached all the nodes
			return false;
	}
	return true;
}

void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& distance) {
	//create queue for bfs and push the start vertex
	queue<int> queue;
	queue.push(startVertex);
	while (!queue.empty()) {
		startVertex = queue.front();
		// for each neighbors of 'i' vertex
		for (auto i : graph->adjList[startVertex]) {
			// mark as visited, push into the queue, save distance from starting node
			if (!visited[i]) {
				visited[i] = true;
				queue.push(i);
				distance[i] = distance[startVertex] + 1;
			}
		}
		queue.pop();
	}
}

int Test1(int V, int itr, float P) {
	int counter = 0; // counter for a number of connected graphs
	for (int i = 0; i < itr; i++) {
		Graph* graph = build_random_graph(V, P);
		bool test = connectivity(graph);
		if (test)
			counter++;

		delete[] graph->adjList;
		delete graph;
	}
	return counter;
}


//Test2 function without using threads
/*int Test2(int V, int itr, float P) {
	int counter = 0; // counter for graphs with diamter of 2
	for (int i = 0; i < itr; i++) {
		Graph* graph = build_random_graph(V, P);
		int test = diameter(graph);
		if (test <= 2)
			counter++;

		delete[] graph->adjList;
		delete graph;
	}
	return counter;
}*/


int Test2(int V, int itr, float P) {
	vector<future<void>> runTest2Async(itr); // array for storing the asyncs
	vector<int> counter(itr, 0);// counter for graphs with diamter of 2, size of itr and 0 values
	for (int i = 0; i < itr; i++) {
		// running in 500 threads for each graph
		runTest2Async[i] = std::async(test2Loop, i, i + 1, V, P, &counter, itr);
	}
	//waiting for async to finish
	for (int i = 0; i < itr; i++) {
		runTest2Async[i].wait();
	}
	int sum = 0;// sum of the values in counter (diameter of current graph)
	for (int i = 0; i < itr; i++) {
		sum += counter[i];
	}
	return sum;
}

void test2Loop(int start, int end, int V, float P, vector<int>* counter, int itr)
{
	for (int i = start; i < end; i++) {
		Graph* graph = build_random_graph(V, P);
		int test = diameter(graph);
		if (test <= 2)
			(*counter)[i] ++;

		delete[] graph->adjList;
		delete graph;
	}
}

int Test3(int V, int itr, float P) {
	int counter = 0; // counter for graphs with isolated vertices
	for (int i = 0; i < itr; i++) {
		Graph* graph = build_random_graph(V, P);
		bool test = Is_Isolated(graph);
		if (test)
			counter++;

		delete[] graph->adjList;
		delete graph;
	}
	return counter;
}


int main() {
	const int V = 1000; // number of vertices
	const int itr = 500; // number of graphs
	// thershold 0.00690775527
	float P1000[10] = { 0.005f, 0.0057f, 0.0059f,0.006f, 0.00690775527f,
		0.00699f, 0.00788f, 0.00888f, 0.00999f, 0.012f };
	// threshold 0.11753940002
	float P2_1000[10] = { 0.11f , 0.112f , 0.113f, 0.114f, 0.11753940002f,
		0.1178f, 0.12f, 0.125f, 0.13f, 0.135f };
	// opens an existing csv file or creates a new file.
	ofstream file;
	file.open("ConnectivityTest.csv");

	file << "test1," << "Probabilty, connectivity, nubmer of graphs, connectivity, number of graphs" << endl;
	auto start = std::chrono::high_resolution_clock::now();// starts time here
	for (int i = 0; i < 10; i++) {
		int test1 = Test1(V, itr, P1000[i]);
		file << "," << P1000[i] << ":, true: ," << test1 << ", false: ," << (itr - test1) << endl;
		cout << "P" << i + 1 << " finished in test1" << endl;
	}
	cout << "test1 is finished" << endl;
	file.close();
	file.open("DiameterTest.csv");
	file << "test2, Probability, diameter <= 2, diameter > 2" << endl;
	for (int i = 0; i < 10; i++) {
		int test2 = Test2(V, itr, P2_1000[i]);
		file << "," << P2_1000[i] << ":, " << test2 << ", " << (itr - test2) << endl;
		cout << "P " << i + 1 << " finished in test2" << endl;
	}
	cout << "test2 is finished" << endl;
	file.close();
	file.open("isIsolatedTest.csv");
	file << "test3, Probability, number of isolated vertices, number of non isolated vertices" << endl;
	for (int i = 0; i < 10; i++) {
		int test3 = Test3(V, itr, P1000[i]);
		file << "," << P1000[i] << ":, " << test3 << ", " << (itr - test3) << endl;
		cout << "P" << i + 1 << " finished in test3" << endl;
	}
	auto stop = std::chrono::high_resolution_clock::now(); //stops time here
	cout << "test3 is finished" << endl;
	cout << ((stop - start) / 1000000).count(); //time in milliseconds

	file.close();
	return 0;
}