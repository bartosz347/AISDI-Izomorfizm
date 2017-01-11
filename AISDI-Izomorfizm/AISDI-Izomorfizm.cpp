#include "stdafx.h"


int main(int argc, const char *argv[])
{

#ifdef _DEBUG
	(void)argc;
	(void)argv;
	std::string graph1("tests/set20/graf1.txt");
	std::string graph2("tests/set20/graf2.txt");
#endif // DEBUG		
	
#ifndef _DEBUG
	if (argc != 3) {
		std::cout << "Invalid data" << std::endl;
		return -1;
	}

	std::string graph1(argv[1]);
	std::string graph2(argv[2]);
#endif // !DEBUG
	try
	{
		Graph<int> G1(graph1);
		Graph<int> G2(graph2);
		Isomorphism<int> isomorphism(G1, G2);
		isomorphism.checkIsomorphism();
	}
	catch (const std::exception&)
	{
		std::cout << "Error" << std::endl;
		return -1;
	}
	

#ifdef _DEBUG
	std::system("pause");
#endif // DEBUG	
	return 0;
}

