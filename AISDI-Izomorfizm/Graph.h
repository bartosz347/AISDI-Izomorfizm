#pragma once

#include <vector>
#include <fstream>
#include <algorithm>

template <typename K>
class Graph
{
public:

	Graph(const K &verticesNo) : adjMatrix(std::vector<std::vector<bool>>(verticesNo, std::vector<bool>(verticesNo))), verticesNo(verticesNo)
	{}
	Graph(std::string fileName) 
	{
		loadFromFile(fileName);
	}

	K verticesNo;
	K edgesNo;

	void insertEdge(const K &begin, const K &end)
	{
		if (begin >= verticesNo || end >= verticesNo)
			throw std::invalid_argument("invalid vertex id");

		adjMatrix[begin][end] = 1;
		adjMatrix[end][begin] = 1;
		edgesNo++;
	}

	bool isEdge(const K &begin, const K &end) const
	{
		return adjMatrix[begin][end] == 1;
	}

	const K getInvariant(const K &node) const
	{
		return getNodeTwoPath(node);
		//return getNodeDegree(node);
	}

	~Graph()
	{}
private:
	std::vector< std::vector<bool> > adjMatrix;

	void loadFromFile(std::string filename)
	{
		std::fstream fs;
		fs.open(filename, std::fstream::in);
		int v1, v2;
		fs >> verticesNo;
		adjMatrix = std::vector<std::vector<bool>>(verticesNo, std::vector<bool>(verticesNo));
		while (fs >> v1 && fs >> v2)
			insertEdge(v1, v2);
		fs.close();
	}

	const K getNodeDegree(const K &node) const
	{
		int degree = 0;
		for (auto elem : adjMatrix[node])
			if (elem == 1) degree++;
		return degree;
	}

	const K getNodeTwoPath(const K &node) const
	{
		std::vector<K> p;
				
		for (K i = 0; i < verticesNo; i++)
		{
			if (adjMatrix[node][i] == 1)
			{
				for (K j = 0; j < verticesNo; j++)
				{
					if(adjMatrix[i][j] == 1 && std::find(p.begin(),p.end(),j) == p.end()) // edge exists and vertex not yet counted
						p.push_back(j);
				}
			}
		}

		return static_cast<K>(p.size());
	}

	
};

template class Graph<int>;