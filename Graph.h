#pragma once
#include <map>
#include <vector>
#include <utility>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;



class Graph
{
private:
	map<int, vector<pair<int, int>>> inboundEdges;
	map<int, vector<pair<int, int>>> outboundEdges;
	int verticesNumber;
	int edgesNumber;

public:
	Graph(int verticesNumber);
	int getVerticesNumber();
	int getEdgesNumber();
	int getInDegree(int vertex);
	int getOutDegree(int vertex);
	int getCost(int start, int end);

	void setEdgesNumber(int edgesNumber);
	void setCost(int start, int end, int newCost);

	vector<int> parseVertices();
	vector<pair<int, int>> parseVertexOutbound(int vertex);
	vector<pair<int, int>> parseVertexInbound(int vertex);

	void addVertex(int vertex);
	void removeVertex(int vertex);
	void addEdge(int start, int end, int cost);
	bool isEdge(int start, int end);
	void removeEdge(int start, int end);

	void printGraph();
	
};