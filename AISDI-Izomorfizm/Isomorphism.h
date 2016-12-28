#pragma once

#include <vector>
#include "Graph.h"

template <typename K>
class Isomorphism
{
public:

	class Vertex
	{
	public:
		Vertex() : isUsed(false) {}
		Vertex(K no) : no(no), isUsed(false) {}
		K no;
		bool isUsed;
	};
	Isomorphism(const Graph<K> &G1, const Graph<K> &G2) : G1(G1), G2(G2), bijectionFunctionf(G1.verticesNo, -1), verticesFromG2f(G2.verticesNo)
	{
		for (K i = 0; i < G2.verticesNo; i++)
		{
			verticesFromG2f[i].no = i;
		}
	}

	bool checkIsomorphism()
	{
		if (G1.verticesNo != G2.verticesNo)
			return false;

		if (isomorph(0, verticesFromG2f, bijectionFunctionf))
			return true;
		else
			return false;

		// invariants calculate and so


	}

	bool isomorph(K k, std::vector<Vertex> verticesFromG2, std::vector<K> bijectionFunction)
	{
		if (k == G1.verticesNo)
			return true; // all vertices matched ( we have G1.verticesNo vertices )

		for (auto vertex : verticesFromG2) {
			if (vertex.isUsed == true || !canBeMatched(k, vertex, bijectionFunction)) // we check all vertices from G2 that aren't yet mapped
				continue;
			
			
			std::vector<Vertex> verticesFromG2_(verticesFromG2);
			verticesFromG2_[vertex.no].isUsed = true;

			std::vector<K> bijectionFunction_(bijectionFunction);
			bijectionFunction_[k] = vertex.no; // we've found a vertex in G2 that can be matched, so we save it in bijectionFunction

			if (isomorph(k + 1, verticesFromG2_, bijectionFunction_)) // let's try to extend it to k+1 subgraph of G1
				return true;

			// if extending fails - we proceed with the next unused vertex from G2
			//bijectionFunction[k] = -1; // is that right? TODO	
			//verticesFromG2[vertex.no].isUsed = false; 		
		}

		return false;
	}

	
	~Isomorphism()
	{}
private:
	class Vertex;
	Graph<K> G1; // we start by taking subgraphs G1(k) and trying to extend by adding from G2
	Graph<K> G2;

	std::vector<Vertex> verticesFromG2f;
	std::vector<K> bijectionFunctionf;

	bool canBeMatched(const K &k, const Vertex &vertex, std::vector<K> bijectionFunction)
	{
		for (K i = 0; i < G1.verticesNo; i++)
		{
			if(bijectionFunction[i] != -1)
				if (G1.isEdge(i, k) != G2.isEdge(bijectionFunction[i], vertex.no)) {
					return false;
				}
		}
		return true;

	}




};

