#include "Graph.h"



Graph::Graph(int verticesNumber)
{
	this->verticesNumber = verticesNumber;
	this->edgesNumber = 0;
	for (int vertex = 0; vertex < verticesNumber; vertex++)
	{
		this->inboundEdges[vertex] = vector<pair<int, int>>();
		this->outboundEdges[vertex] = vector<pair<int, int>>();
	}
}

int Graph::getVerticesNumber()
{
	return this->verticesNumber;
}

int Graph::getEdgesNumber()
{
	return this->edgesNumber;
}

int Graph::getInDegree(int vertex)
{
	return this->inboundEdges[vertex].size();
}

int Graph::getOutDegree(int vertex)
{
	return this->outboundEdges[vertex].size();
}

int Graph::getCost(int start, int end)
{
	for (int i = 0; i < this->outboundEdges[start].size(); i++)
		if (this->outboundEdges[start][i].first == end)
			return this->outboundEdges[start][i].second;
}

void Graph::setEdgesNumber(int edgesNumber)
{
	this->edgesNumber = edgesNumber;
}

void Graph::setCost(int start, int end, int newCost)
{
	
}

vector<int> Graph::parseVertices()
{
	vector<int> vertices;
	for (auto vertex : this->outboundEdges)
		vertices.push_back(vertex.first);
	return vertices;
}

vector<pair<int, int>> Graph::parseVertexOutbound(int vertex)
{
	return this->outboundEdges[vertex];
}

vector<pair<int, int>> Graph::parseVertexInbound(int vertex)
{
	return this->inboundEdges[vertex];
}

void Graph::addVertex(int vertex)
{
	this->inboundEdges[vertex] = vector<pair<int, int>>();
	this->outboundEdges[vertex] = vector<pair<int, int>>();
	this->verticesNumber++;
}

void Graph::removeVertex(int vertex)
{
	auto it = this->outboundEdges.find(vertex);
	this->outboundEdges.erase(it);
	it = this->inboundEdges.find(vertex);
	this->inboundEdges.erase(it);
	for (auto v : this->outboundEdges)
		for (int j = 0; j < v.second.size(); j++)
			if (v.second[j].first == vertex)
				v.second.erase(v.second.begin() + j);
	for (auto v : this->inboundEdges)
		for (int j = 0; j < v.second.size(); j++)
			if (v.second[j].first == vertex)
				v.second.erase(v.second.begin() + j);
	this->verticesNumber--;
}

void Graph::addEdge(int start, int end, int cost)
{
	this->outboundEdges[start].push_back(make_pair(end, cost));
	this->inboundEdges[end].push_back(make_pair(start, cost));
	this->edgesNumber++;
}

bool Graph::isEdge(int start, int end)
{
	for (int i = 0; i < this->outboundEdges[start].size(); i++)
		if (this->outboundEdges[start][i].first == end)
			return true;
	return false;
}

void Graph::removeEdge(int start, int end)
{
	for (int i = 0; i < this->outboundEdges[start].size(); i++)
		if (this->outboundEdges[start][i].first == end)
			this->outboundEdges[start].erase(this->outboundEdges[start].begin() + i);
	
	for (int i = 0; i < this->inboundEdges[end].size(); i++)
		if (this->inboundEdges[end][i].first == start)
			this->inboundEdges[end].erase(this->inboundEdges[end].begin() + i);
	this->edgesNumber--;
}

void Graph::printGraph()
{
	cout << "Inbound Edges\n";
	for (auto vertex : this->inboundEdges)
	{
		cout << vertex.first << " : ";
		for (auto edge : vertex.second)
			cout << "(" << edge.first << " " << edge.second << ")" << " ";
		cout << "\n";
	}
	cout << "\nOutbound Edges\n";
	for (auto vertex : this->outboundEdges)
	{
		cout << vertex.first << " : ";
		for (auto edge : vertex.second)
			cout << "(" << edge.first << " " << edge.second << ")" << " ";
		cout << "\n";
	}
}

Graph readFromFile(string fileName)
{
	ifstream fin(fileName);
	int verticesNumber, edgesNumber, startVertex, endVertex, cost;
	fin >> verticesNumber >> edgesNumber;
	Graph graph = Graph(verticesNumber);
	for (int i = 0; i < edgesNumber - 1; i++)
	{
		fin >> startVertex >> endVertex >> cost;
		graph.addEdge(startVertex, endVertex, cost);
	}
	graph.setEdgesNumber(edgesNumber);
	return graph;
	
}
void writeToFile(Graph graph, string fileName)
{
	ofstream fout("C:\\Users\\Tudor\\Desktop\\test.txt");
	fout << "TEST";
	fout << graph.getVerticesNumber() << " " << graph.getEdgesNumber();
	fout << "\n";
	for (auto vertex : graph.parseVertices())
	{
		for (auto mapVertex : graph.parseVertexOutbound(vertex))
		{
			fout << vertex << " " << mapVertex.first << " " << mapVertex.second << "\n";
		}
	
	}
}

int main()
{
	Graph graph = readFromFile("graph.txt");
	graph.printGraph();
	writeToFile(graph, "‪C:\\Users\\Tudor\\Desktop\\test.txt");
	return 0;
}