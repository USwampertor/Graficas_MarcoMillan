#include <stdio.h>
#include <IDVParser.h>
#include <string>
#include <vector>
#include <fstream>

void PrintFromLibrary()
{
	printf("Hello World from static library \n");
}
struct vertex
{
	float x, y, z;

};
class Parser
{
	
	bool Load(std::string filename)
	{
		std::string checker = "mesh_";
		float ftest;
		std::string a, b;
		char c, cont;
		std::vector<vertex*> model;
		std::vector<vertex*>::iterator mit;
		int size = 0;
		int totalvert = 0;
		bool trigger = false;
		std::ifstream mreader;
		mreader.open(filename);
		if (!mreader.is_open())
		{
			return false;
		}
		else
		{
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

		}
	}
};