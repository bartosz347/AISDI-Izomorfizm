// AISDI-Izomorfizm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char *argv)
{
	std::fstream fs;
	int verticesNo;

	fs.open("graf1.txt", std::fstream::in);
	fs >> verticesNo;
	fs.close();
	Graph<int> G1(verticesNo);
	G1.loadFromFile("graf1.txt");

	fs.open("graf2.txt", std::fstream::in);
	fs >> verticesNo;
	fs.close();
	Graph<int> G2(verticesNo);
	G2.loadFromFile("graf2.txt");

	Isomorphism<int> isomorphism(G1, G2);

	isomorphism.checkIsomorphism();

	

	return 0;
}

