// AISDI-Izomorfizm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, const char *argv[])
{

#ifdef _DEBUG
	std::string graph1("graf1_bb.txt");
	std::string graph2("graf2_bb.txt");
#endif // DEBUG		
	
#ifndef _DEBUG
	if (argc != 3) {
		std::cout << "Invalid data" << std::endl;
		return -1;
	}

	std::string graph1(argv[1]);
	std::string graph2(argv[2]);
#endif // !DEBUG


	std::fstream fs;
	int verticesNo;

	fs.open(graph1, std::fstream::in);
	fs >> verticesNo;
	fs.close();
	Graph<int> G1(verticesNo);
	G1.loadFromFile(graph1);

	fs.open(graph2, std::fstream::in);
	fs >> verticesNo;
	fs.close();
	Graph<int> G2(verticesNo);
	G2.loadFromFile(graph2);

	Isomorphism<int> isomorphism(G1, G2);
	isomorphism.checkIsomorphism();


	std::system("pause");
	return 0;
}

