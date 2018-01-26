#include <stdio.h>
#include <IDVParser.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
void PrintFromLibrary()
{
	printf("Hello World from static library \n");
}
Parser::Parser()
{
	checker = "mesh_";
	ftest = 0;
	size = 0;
	totalvert = 0;
}
bool Parser::Load(std::string filename)
{
		
		std::vector<vertex*> model;
		std::vector<vertex*>::iterator mit;
		std::ifstream mreader;
		mreader.open(filename);
		if (!mreader.is_open())
		{
			return false;
		}
		
		mreader.seekg(0, mreader.end);
		size = mreader.tellg();
		mreader.seekg(0, mreader.beg);

		while (true)
			{
				mreader >> a;
				if (a == "Mesh")
				{
					mreader >> a;
					b = a.substr(0, 5);
					if (b == checker)
					{
						break;
					}

				}
			}
		mreader >> c >> totalvert >> c;

		for (int i = 0; i < totalvert; i++)
			{
				vertex *p = new vertex;
				mreader >> p->x >> c >> p->y >> c >> p->z >> c >> c;

				model.push_back(p);
			}
		mreader.close();
		std::cout << "holi" << std::endl;
		for (mit=model.begin(); mit!= model.end(); mit++)
		{
			std::cout<< "x:"<< (*mit)->x<<" y: "<<(*mit)->y<<" z: " <<(*mit)->z<<std::endl;
		}
		return true;
		
};
