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
	
	~Isomorphism()
	{}
private:
	const Graph<K> &G1; // we start by taking subgraphs G1(k) and trying to extend by adding from G2
	const Graph<K> &G2;

	std::vector<K> invariantsG1;
	std::vector<K> invariantsG2;
	std::vector<K> finalBijectionFunction;

	class Vertex
	{
	public:
		Vertex(K no = -1) : no(no), isUsed(false) {}
		K no;
		bool isUsed;
	};

	bool runIsomorphismCheck() 
	{
		if (G1.vertexCount != G2.vertexCount || G1.edgeCount != G2.edgeCount)
			return false;

		calculateInvariants();

		std::vector<Vertex> verticesFromG2(G2.vertexCount);
		std::vector<K> bijectionFunction(G1.vertexCount, -1);
		for (size_t i = 0; i < G2.vertexCount; i++)
		{
			verticesFromG2[i].no = i;
		}

		if (isomorph(0, verticesFromG2, bijectionFunction)) {
			return true;
		}
		else
			return false;
	}

	bool isomorph(const K &currentlyMatchedVertexNo, const std::vector<Vertex> &verticesFromG2, const std::vector<K> &bijectionFunction)
	{
		if (currentlyMatchedVertexNo == G1.vertexCount) {
			finalBijectionFunction = std::move(bijectionFunction);
			return true; // all vertices matched ( we have G1.verticesNo vertices )			
		}

		for (auto vertex : verticesFromG2) {
			if (vertex.isUsed == true || !canBeMatched(Vertex(currentlyMatchedVertexNo), vertex, bijectionFunction)) // we check all vertices from G2 that aren't yet mapped
				continue;

			std::vector<Vertex> verticesFromG2_new(verticesFromG2);
			std::vector<K> bijectionFunction_new(bijectionFunction);
			verticesFromG2_new[vertex.no].isUsed = true;
			bijectionFunction_new[currentlyMatchedVertexNo] = vertex.no; // we've found a vertex in G2 that can be matched, so we save it in bijectionFunction

			if (isomorph(currentlyMatchedVertexNo + 1, verticesFromG2_new, bijectionFunction_new)) // let's try to extend it to k+1 subgraph of G1
				return true;

			// if extending fails - we go back and proceed with the next vertex
		}
		return false;
	}

	bool canBeMatched(const Vertex &vertexFromG1, const Vertex &vertexFromG2, const std::vector<K> &bijectionFunction) const
	{		
		// invariants equality is necessary (but not sufficient)
		if (invariantsG1[vertexFromG1.no] != invariantsG2[vertexFromG2.no])
			return false;

		// let's check the new vertex
		for (size_t i = 0; i < G1.vertexCount; i++)
		{
			if(bijectionFunction[i] != -1)
				if (G1.isEdge(i, vertexFromG1.no) != G2.isEdge(bijectionFunction[i], vertexFromG2.no)) {
					return false;
				}
		}
		return true;
	}

	void printBijectionFunction() const
	{
		int i = 0;
		for (auto elem : finalBijectionFunction) {
			std::cout << i << " --> " << elem << std::endl;
			i++;
		}

	}

	void calculateInvariants()
	{
		for (size_t i = 0; i < G1.vertexCount; i++)
		{
			invariantsG1.push_back(G1.getInvariant(i));
			invariantsG2.push_back(G2.getInvariant(i));
		}
	}

};

