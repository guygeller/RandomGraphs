#include<iostream>
#include<list>
#include<set>
#include<vector>
#include<algorithm>
#include<fstream>
#include<cmath>
#define INF 2 << 22 // ~~830k
using namespace std;

struct Graph {
	int V; // count of the nodes in the graph
	set<int, greater<int> >* adjList;
};

//fucntions:
void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& dist);
void addEdge(Graph* graph, int src, int dest);
Graph* build_random_graph(int V, float p);
int diameter(Graph* graph);
bool Is_Isolated(Graph* graph);
bool connectivity(Graph* graph);
void create();
int Test1(int V, int itr, float P);
int Test2(int V, int itr, float P);
int Test3(int V, int itr, float P);



// A utility function that creates a graph of V vertices
Graph* createGraph(int V)
{
	Graph* graph = new Graph;
	graph->V = V;

	// Create an array of sets representing
	// adjacency lists.  Size of the array will be V
	graph->adjList = new set<int, greater<int> >[V];

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest)
{
	// Add an edge from src to dest.  A new
	// element is inserted to the adjacent
	// list of src.
	graph->adjList[src].insert(dest);

	// Since graph is undirected, add an edge
	// from dest to src also
	graph->adjList[dest].insert(src);
}


//A utility function to print the adjacency
//list representation of graph
//void printGraph(Graph* graph)
//{
//	for (int i = 0; i < graph->V; ++i) {
//		set<int, greater<int> > lst = graph->adjList[i];
//		cout << i << ": ";
//		for (auto itr = lst.begin(); itr != lst.end(); ++itr)
//			cout << *itr << " ";
//		cout << endl;
//	}
//
//}

//Searches for a given edge in the graph
//int searchEdge(Graph* graph, int src, int dest)
//{
//	auto itr = graph->adjList[src].find(dest);
//
//	if (itr == graph->adjList[src].end())
//		/*cout << endl << "Edge from " << src
//		<< " to " << dest << " not found."
//		<< endl;*/
//		return 0;
//	else
//		/*cout << endl << "Edge from " << src
//		<< " to " << dest << " found."
//		<< endl;*/
//		return 1;
//}


Graph* build_random_graph(int V, float P) {
	Graph* graph;
	graph = createGraph(V);
	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++)
		{
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
		vector<bool> visited;
		vector<int> dist;
		BFS(graph, i, visited, dist);
		// distance from the start vertex to the farthest leaf
		int max_dist = *max_element(dist.begin(), dist.end());
		if (max_dist == INF)
			return INF;
		if (diameter < max_dist)
			diameter = max_dist;
	}
	return diameter;
}

bool Is_Isolated(Graph* graph) {

	for (int i = 0; i < graph->V; i++) {
		// check if the "i" node has neighbors attached with an edge
		if (graph->adjList[i].empty())
			return true;
	}
	return false;
}

bool connectivity(Graph* graph) {
	vector<bool> visited;
	vector<int> dist;

	BFS(graph, 0, visited, dist);

	//stating from the second vertex
	for (int i = 1; i < graph->V; i++) {
		if (!visited[i]) // if not visited that means BFS fucntion hasn't reached all the nodes
			return false;
	}
	return true;
}

void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& distance) {
	// resize the vectors (visited and distance arrays) and intialise with false
	visited.resize(graph->V, false);
	distance.resize(graph->V, INF);

	for (int v = 0; v < graph->V; ++v) {
		distance[v] = INF;
		visited[v] = false;
	}
	// initialising the start vertex
	distance[startVertex] = 0;
	visited[startVertex] = true;

	//create queue for bfs and push the start vertex
	list<int> queue;
	queue.push_back(startVertex);

	while (!queue.empty())
	{
		startVertex = queue.front();
		queue.pop_front();
		// for each neighbors of 'i' vertex
		for (auto i : graph->adjList[startVertex])
		{
			// mark as visited, push into the queue, save distance from starting node
			if (!visited[i])
			{
				visited[i] = true;
				queue.push_back(i);
				distance[i] = distance[startVertex] + 1;
			}
		}
	}
}

//void create()//write to CSV file
//{
//	ofstream file;
//	// opens an existing csv file or creates a new file.
//	file.open("Test.csv");
//	for (int i = 0; i < 10; i++) { // 10 tests for each P value
//		// Insert the data to file
//		file << endl;
//	}
//	file.close();
//}

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

int Test2(int V, int itr, float P) {
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
	int V = 1000; // number of vertices
	int itr = 500;
	//float P100[10] = { 0.009, 0.01, 0.015, 0.02, 0.045, 0.05, 0.06, 0.07, 0.08, 0.09 };
	float P1000[10] = { 0.0007, 0.001, 0.002, 0.003, 0.006, 0.008, 0.01, 0.012, 0.014, 0.016 };
	ofstream file;
	// opens an existing csv file or creates a new file.

	file.open("Test.csv");
	file << "test1," << "Probabilty, connectivity, nubmer of graphs, connectivity, number of graphs" << endl;
	for (int i = 0; i < 10; i++)
	{
		int test1 = Test1(V, itr, P1000[i]);
		file << "," << P1000[i] << ":, true: ," << test1 << ", false: ," << (itr - test1) << endl;

	}
	file << "test2, Probability, diameter" << endl;

	//float P2_100[10] = { 0.5, 0.1, 0.15, 0.2, 0.25, 0.3, 0.5, 0.65, 0.8, 0.9 };
	float P2_1000[10] = { 0.03 , 0.04 , 0.05, 0.06, 0.08, 0.09, 0.1, 0.3, 0.5, 0.8 };
	for (int i = 0; i < 10; i++)
	{
		int test2 = Test2(V, itr, P2_1000[i]);
		file << "," << P2_1000[i] << ": , " << test2 << endl;
	}
	file << "test3, Probability, number of isolated" << endl;
	for (int i = 0; i < 10; i++)
	{
		int test3 = Test2(V, itr, P1000[i]);
		file << "," << P1000[i] << ":, " << test3 << endl;
	}
	file.close();
	//int ok = 0;
	/*for (int i = 0; i < 100; i++) {
		Graph* graph1 = build_random_graph(1000, 0.012);
		if (connectivity(graph1))
			ok++;
		delete[] graph1->adjList;
		delete graph1;
	}*/
	//cout << ok;
	//Graph* graph1 = build_random_graph(7, 0.5);
	//printGraph(graph1);
	//cout << is_isolated(graph1)<<endl;
	//cout << diameter(graph1);
	//create();
	return 0;
}