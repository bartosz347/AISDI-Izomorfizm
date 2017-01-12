#pragma once

#include <vector>
#include <fstream>
#include <algorithm>

template <typename K>
class Graph
{
public:
	Graph(const K &verticesNo) : vertexCount(verticesNo)
	{
		adjMatrix = std::vector<std::vector<bool>>(verticesNo);
		for (size_t i = 0; i < verticesNo; i++) {
			adjMatrix[i] = std::vector<bool>(i + 1, 0);
		}
	}

	Graph(std::string fileName) 
	{
		loadFromFile(fileName);
	}

	K vertexCount;
	K edgeCount;

	void insertEdge(const K &begin, const K &end)
	{
		if (begin >= vertexCount || end >= vertexCount)
			throw std::invalid_argument("invalid vertex id");

		if (begin == end)
			throw std::invalid_argument("");

		begin >= end ? adjMatrix[begin][end] = 1 : adjMatrix[end][begin] = 1;
		edgeCount++;
	}

	bool isEdge(const K &begin, const K &end) const
	{
		return begin >= end ? adjMatrix[begin][end] == 1 : adjMatrix[end][begin] == 1;
	}

	const K getInvariant(const K &node, int type = 0) const
	{
		if(type == 0)
			return getNodeTwoPath(node);
		else
			return getNodeDegree(node);
	}

	~Graph()
	{}
private:
	std::vector< std::vector<bool> > adjMatrix;

	void loadFromFile(std::string filename)
	{
		std::fstream fs;
		fs.open(filename, std::fstream::in);
		if (!fs.good())
			throw std::runtime_error("cannot open file");
		int v1, v2;
		fs >> vertexCount;
		adjMatrix = std::vector<std::vector<bool>>(vertexCount);
		for (size_t i = 0; i < vertexCount; i++)	{
			adjMatrix[i] = std::vector<bool>(i+1, 0);
		}
		while (fs >> v1 && fs >> v2)
			insertEdge(v1, v2);
		fs.close();
	}

	const K getNodeDegree(const K &node) const
	{
		int degree = 0;
		for (auto elem : adjMatrix[node])
			if (elem == 1) degree++;

		for (size_t i = node+1; i < vertexCount; i++)	{
			if (adjMatrix[i][node] == 1)
				degree++;
		}
		return degree;
	}

	void addNewVertexesThatNodeIsLinkedWith(std::vector<K> &p, K node) const
	{
		K i = 0;
		for (auto elem : adjMatrix[node]) {
			if (elem == 1 && std::find(p.begin(), p.end(), i) == p.end()) 
				p.push_back(i);			
			i++;
		}

		for (size_t i = node + 1; i < vertexCount; i++) {
			if (adjMatrix[i][node] == 1 && std::find(p.begin(), p.end(), i) == p.end())
				p.push_back(i);
		}
	}

	const K getNodeTwoPath(const K &node) const
	{
		std::vector<K> p;
		size_t i = 0;
		for (auto elem : adjMatrix[node]) {
			if (elem == 1) 
				addNewVertexesThatNodeIsLinkedWith(p, i);
			i++;
		}

		for (size_t i = node + 1; i < vertexCount; i++) {
			if (adjMatrix[i][node] == 1)
				addNewVertexesThatNodeIsLinkedWith(p, i);
		}

		return static_cast<K>(p.size());
	}
	
};

template class Graph<int>;