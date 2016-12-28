#pragma once

#include <vector>
#include <iostream>
#include "Graph.h"

template <typename K>
class Isomorphism
{
public:


	Isomorphism(const Graph<K> &G1, const Graph<K> &G2) : G1(G1), G2(G2)
	{}

	void checkIsomorphism()
	{
		if (runIsomorphismCheck() == true) {
			std::cout << "Izomorficzne" << std::endl;
			printBijectionFunction();
		}
		else
			std::cout << "Nieizomorficzne" << std::endl;
	}

	bool runIsomorphismCheck()
	{
		if (G1.verticesNo != G2.verticesNo)
			return false;
		
		std::vector<Vertex> verticesFromG2(G2.verticesNo);
		std::vector<K> bijectionFunction(G1.verticesNo, -1);
		for (K i = 0; i < G2.verticesNo; i++)
		{
			verticesFromG2[i].no = i;
		}

		// invariants calculate and so

		if (isomorph(0, verticesFromG2, bijectionFunction)) {
			return true;
		}
		else
			return false;
	}

	

	
	~Isomorphism()
	{}
private:
	Graph<K> G1; // we start by taking subgraphs G1(k) and trying to extend by adding from G2
	Graph<K> G2;

	std::vector<K> finalBijectionFunction;

	class Vertex
	{
	public:
		Vertex() : isUsed(false) {}
		Vertex(K no) : no(no), isUsed(false) {}
		K no;
		bool isUsed;
	};

	bool isomorph(K k, std::vector<Vertex> &verticesFromG2, std::vector<K> &bijectionFunction)
	{
		if (k == G1.verticesNo) {
			finalBijectionFunction = std::move(bijectionFunction);
			return true; // all vertices matched ( we have G1.verticesNo vertices )			
		}

		for (auto vertex : verticesFromG2) {
			if (vertex.isUsed == true || !canBeMatched(k, vertex, bijectionFunction)) // we check all vertices from G2 that aren't yet mapped
				continue;

			std::vector<Vertex> verticesFromG2_new(verticesFromG2);
			std::vector<K> bijectionFunction_new(bijectionFunction);
			verticesFromG2_new[vertex.no].isUsed = true;
			bijectionFunction_new[k] = vertex.no; // we've found a vertex in G2 that can be matched, so we save it in bijectionFunction

			if (isomorph(k + 1, verticesFromG2_new, bijectionFunction_new)) // let's try to extend it to k+1 subgraph of G1
				return true;

			// if extending fails - we proceed with the next unused vertex from G2		
		}
		return false;
	}

	bool canBeMatched(const K &k, const Vertex &vertex, const std::vector<K> &bijectionFunction) const
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

	void printBijectionFunction()
	{
		int i = 0;
		for (auto elem : finalBijectionFunction) {
			std::cout << i << " --> " << elem << std::endl;
			i++;
		}

	}




};

