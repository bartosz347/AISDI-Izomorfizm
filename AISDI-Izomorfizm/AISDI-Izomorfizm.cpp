#include "stdafx.h"

Graph<int> loadGraphFromFile(std::string filename);
void printGraphCheckResult(const std::vector<int>& bijectionFunction);


int main(int argc, const char *argv[])
{

#ifdef _DEBUG
	(void)argc;
	(void)argv;
	std::string graph1("tests/4/graf1.txt");
	std::string graph2("tests/4/graf2.txt");
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
		Graph<int> G1 = std::move(loadGraphFromFile(graph1));
		Graph<int> G2 = std::move(loadGraphFromFile(graph2));		
		Isomorphism<int> isomorphism(G1, G2);

		printGraphCheckResult(isomorphism.getBijectionFunction());	
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



Graph<int> loadGraphFromFile(std::string filename)
{
	std::fstream fs;
	fs.open(filename, std::fstream::in);
	if (!fs.good())
		throw std::runtime_error("cannot open file");
	int v1, v2;
	int vertexCount;
	fs >> vertexCount;
	Graph<int> G(vertexCount);
	while (fs >> v1 && fs >> v2)
		G.insertEdge(v1, v2);
	fs.close();
	return G;
}


void printGraphCheckResult(const std::vector<int>& bijectionFunction)
{
	if (bijectionFunction.size() != 0) {
		std::cout << "Izomorficzne" << std::endl;
		int i = 0;
		for (auto elem : bijectionFunction) {
			std::cout << i << " --> " << elem << std::endl;
			i++;
		}

	} else
		std::cout << "Nieizomorficzne" << std::endl;
}

