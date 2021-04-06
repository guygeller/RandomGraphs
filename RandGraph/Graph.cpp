
#include<iostream>
#include<list>
#include<set>
#include <vector>
#define INF 2 << 22
using namespace std;

struct Graph {
	int V;
	set<int, greater<int> >* adjList;
};


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
		for (auto itr = lst.begin(); itr != lst.end(); ++itr)
			cout << *itr << " ";
		cout << endl;
	}

}

//Searches for a given edge in the graph
void searchEdge(Graph* graph, int src, int dest)
{
	auto itr = graph->adjList[src].find(dest);
	if (itr == graph->adjList[src].end())
		cout << endl << "Edge from " << src
		<< " to " << dest << " not found."
		<< endl;
	else
		cout << endl << "Edge from " << src
		<< " to " << dest << " found."
		<< endl;
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

}

bool is_isolated(Graph* graph) {
	for (int i = 0; i < 1000; i++) {
		if (graph->adjList[i] == 0) // צריך לגרום לזה לעבוד כי הצד השמאלי זה לא מספר, צריך פונקציה שמחזירה את מספר שכנים שיש
			return true;
	}
	return false;
}

bool connectivity(Graph* graph) {
	BFS(graph, 0);
	// לגשת למערך הפאי.הורים

	for (int i = 1; i < /*size of pie*/; i++) { //stating from the next vertex
		if (/*pie[i]*/ == -1)
			return fasle;
	}
	return true;

}

void BFS(Graph* graph, int startVertex) {
	bool* visited = new bool[1000];
	vector<int> dist;
	vector<int> parent;

	for (int v = 0; v < 1000; ++v) {
		dist[v] = INF;
		parent[v] = -1;
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
				dist.push_back(i++);
				parent.push_back(startVertex);
			}

		}
	}

}


int main() {
	Graph* graph1 = build_random_graph(1000, pHelper());
	printGraph(graph1);
	return 0;
}