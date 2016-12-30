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

	Graph<int> G1(graph1);
	Graph<int> G2(graph2);

	Isomorphism<int> isomorphism(G1, G2);
	isomorphism.checkIsomorphism();


#ifdef _DEBUG
	std::system("pause");
#endif // DEBUG	
	return 0;
}

