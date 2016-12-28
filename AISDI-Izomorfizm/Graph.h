#pragma once

#include <vector>
#include <fstream>

template <typename K>
class Graph
{
public:
	Graph(const K &verticesNo) : adjMatrix(std::vector<std::vector<bool>>(verticesNo, std::vector<bool>(verticesNo))), verticesNo(verticesNo)
	{}
	const K verticesNo;

	void insertEdge(const K &begin, const K &end)
	{
		if (begin >= verticesNo || end >= verticesNo)
			throw std::invalid_argument("invalid vertex id");

		adjMatrix[begin][end] = 1;
		adjMatrix[end][begin] = 1; // todo ?
	}

	void loadFromFile(std::string filename)
	{
		std::fstream fs; 
		fs.open(filename, std::fstream::in);
		int v1, v2;
		fs >> v1;
		while (fs >> v1 && fs >> v2)
			insertEdge(v1, v2);
		fs.close();
	}

	bool isEdge(const K &begin, const K &end) const
	{
		return adjMatrix[begin][end] == 1;
	}

	~Graph()
	{}
private:
	std::vector< std::vector<bool> > adjMatrix;
	
};

template class Graph<int>;