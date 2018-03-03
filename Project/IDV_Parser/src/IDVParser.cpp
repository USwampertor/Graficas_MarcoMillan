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
	vertexchecker = "mesh_";
	uvchecker = "tc0";
	normalchecker = "normals";
	ftest = 0;
	size = 0;
	totalvert = 0;
}
bool Parser::Load(std::string filename)
{
	std::vector<vertex*>::iterator itvert;
	std::vector<uv*>::iterator ituv;
	std::vector<vertex*> vertexbuffer;
	std::vector<uv*> uvbuffer;
	std::vector<normals*> normalbuffer;
	unsigned short ikeeper;
	std::ifstream mreader;
	mreader.open(filename);
	if (!mreader.is_open())
	{
		std::cout << "couldnt find " << filename << "in specified directory" << std::endl;
		return false;
	}
	
	mreader.seekg(0, mreader.end);
	size = mreader.tellg();
	mreader.seekg(0, mreader.beg);
///vertex finder
	while (true)
		{
			mreader >> a;
			if (a == "Mesh")
			{
				mreader >> a;
				b = a.substr(0, 5);
				if (b == vertexchecker)
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
			vertexbuffer.push_back(p);
		}
///index buffer
	mreader >> totalindex >> c;
	for (int index=0;index<totalindex;index++)
	{
		mreader >> c >> c >> ikeeper;
		ParserIndex.push_back(ikeeper);
		mreader >> c >> ikeeper;
		ParserIndex.push_back(ikeeper);
		mreader >> c >> ikeeper;
		ParserIndex.push_back(ikeeper);
		mreader >> c >> c;
	}
///normal buffer
	while (true)
	{
		mreader >> a;
		if (a == "MeshNormals")
		{
			mreader >> a;
			if (a == normalchecker)
			{
				break;
			}

		}
	}
	mreader >> c >> totalnormals >> c;
	for (int i = 0; i < totalnormals; i++)
	{
		normals *p = new normals;
		mreader >> p->nx >> c >> p->ny >> c >> p->nz >> c >> c;
		ParserNorm.push_back(p);
	}
///UV buffer
	while (true)
	{
		mreader >> a;
		if (a == "MeshTextureCoords")
		{
			mreader >> a;
			if (a == uvchecker)
			{
				break;
			}

		}
	}
	mreader >> c >> totaluv >> c;
	for (int i = 0; i < totaluv; i++)
	{
		uv *p = new uv;
		mreader >> p->u >> c >> p->v >> c >> c;
		uvbuffer.push_back(p);
	}
///finished getting all information
	mreader.close();
	for ( itvert = vertexbuffer.begin(),
		ituv = uvbuffer.begin();
		itvert != vertexbuffer.end()&& ituv!=uvbuffer.end();
		itvert++, ituv++
		)
	{
		vertex* p = new vertex;
		p->x = (*itvert)->x;
		p->y = (*itvert)->y;
		p->z = (*itvert)->z;
		p->w = (*itvert)->w;
		p->u = (*ituv)->u;
		p->v = (*ituv)->v;
		ParserVec.push_back(p);
	}
	/*for (itvert = vertanduvbuffer.begin(); itvert != vertanduvbuffer.end(); itvert++)
	{
		std::cout << (*itvert)->x <<" "<< (*itvert)->y << " " << (*itvert)->z << " " << (*itvert)->w << " " << (*itvert)->u << " " << (*itvert)->v << " " << std::endl;
	}*/
	return true;
	
		
};
void Parser::Read()
{
	
	
}