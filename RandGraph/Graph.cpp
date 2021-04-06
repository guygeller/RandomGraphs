
#include<iostream>
#include<list>
#include<set>
#include <vector>
#include <algorithm>
#define INF 2 << 22
using namespace std;
struct Graph {
	int V;
	set<int, greater<int> >* adjList;
};
void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& dist);

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
void printGraph(Graph* graph)
{
	for (int i = 0; i < graph->V; ++i) {
		set<int, greater<int> > lst = graph->adjList[i];
		cout << i << ": ";
		for (auto itr = lst.begin(); itr != lst.end(); ++itr)
			cout << *itr << " ";
		cout << endl;
	}

}

//Searches for a given edge in the graph
int searchEdge(Graph* graph, int src, int dest)
{
	auto itr = graph->adjList[src].find(dest);

	if (itr == graph->adjList[src].end())
		/*cout << endl << "Edge from " << src
		<< " to " << dest << " not found."
		<< endl;*/
		return 0;
	else
		/*cout << endl << "Edge from " << src
		<< " to " << dest << " found."
		<< endl;*/
		return 1;
}

/*
Generates inclusion probability
*/
float pHelper() {
	float pHelper = ((float)rand() / RAND_MAX);
	return pHelper;
}

Graph* build_random_graph(int V, float p) {
	Graph* graph;
	graph = createGraph(V);
	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++)
		{
			float r = ((float)rand() / (RAND_MAX + 1.0));
			if (r <= p)
				addEdge(graph, i, j);
		}
	}
	return graph;
}

int diameter(Graph* graph) {

	int diameter = 0;
	for (int i = 0; i < graph->V; i++) {
		vector<bool> visited;
		vector<int> dist;
		BFS(graph, i, visited, dist);
		int max_dist = *max_element(dist.begin(), dist.end());
		if (max_dist == INF)
			return INF;
		if (diameter < max_dist)
			diameter = max_dist;
	}
	return diameter;
}

bool is_isolated(Graph* graph) {

	for (int i = 0; i < graph->V; i++) {
		if (graph->adjList[i].empty()) // צריך לגרום לזה לעבוד כי הצד השמאלי זה לא מספר, צריך פונקציה שמחזירה את מספר שכנים שיש
			return true;
		continue;
	}
	return false;
}

bool connectivity(Graph* graph) {
	vector<bool> visited;
	vector<int> dist;

	BFS(graph, 0, visited, dist);
	
	for (int i = 1; i < graph->V; i++) { //stating from the next vertex
		if (!visited[i])
			return false;
	}
	return true;

}

void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& dist) {
	visited.resize(graph->V,false);
	dist.resize(graph->V, INF);

	for (int v = 0; v < graph->V; ++v) {
		dist[v] = INF;
		visited[v] = false;
	}
	dist[startVertex] = 0;
	visited[startVertex] = true;

	list<int> queue;
	queue.push_back(startVertex);

	while (!queue.empty())
	{
		startVertex = queue.front();
		queue.pop_front();
		for (auto i : graph->adjList[startVertex])
		{
			if (!visited[i])
			{
				visited[i] = true;
				queue.push_back(i);
				dist[i] = dist[startVertex] + 1;
			}

		}
	}

}


int main() {
	int ok = 0;
	//printGraph(graph1);
	for (int i = 0; i < 100; i++) {
		Graph* graph1 = build_random_graph(1000, 0.012);
		if (connectivity(graph1))
			ok++;
		delete[] graph1->adjList;
		delete graph1;
	}
	cout << ok;
	//cout << is_isolated(graph1)<<endl;
	//cout << diameter(graph1);
	return 0;
}