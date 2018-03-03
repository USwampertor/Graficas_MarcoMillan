#include <stdio.h>
#include <IDVParser.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
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
	std::vector<vertex>::iterator itvert;
	std::vector<uv>::iterator ituv;
	std::vector<normals>::iterator itnormals;
	std::vector<vertex> vertexbuffer;
	std::vector<uv> uvbuffer;
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
			vertex vp;
			mreader >> vp.x >> c >> vp.y >> c >> vp.z >> c >> c;
			vertexbuffer.push_back(vp);
		}
///index buffer
	mreader >> totalindex >> c;
	for (int index=0;index<totalindex;index++)
	{
		unsigned short v0,v1,v2;
		mreader >> c >> c >> v0;
	//	ParserIndex.push_back(ikeeper);
		mreader >> c >> v1;
	//	ParserIndex.push_back(ikeeper);
		mreader >> c >> v2;
	//	ParserIndex.push_back(ikeeper);
		mreader >> c >> c;

		ParserIndex.push_back(v0);
		ParserIndex.push_back(v1);
		ParserIndex.push_back(v2);
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
		normals np;
		mreader >> np.nx >> c >> np.ny >> c >> np.nz >> c >> c;
		ParserNorm.push_back(np);
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
		uv uvp;
		mreader >> uvp.u >> c >> uvp.v >> c >> c;
		uvbuffer.push_back(uvp);
	}
///finished getting all information
	mreader.close();
	for ( itvert = vertexbuffer.begin(),
		ituv = uvbuffer.begin(),
		itnormals=ParserNorm.begin();
		itvert != vertexbuffer.end()&&
		ituv!=uvbuffer.end()&&
		itnormals!=ParserNorm.end();
		itvert++, ituv++,itnormals++
		)
	{
		vertex vpc;
		vpc.x = (*itvert).x;
		vpc.y = (*itvert).y;
		vpc.z = (*itvert).z;
		vpc.w = (*itvert).w;
		vpc.nx = (*itnormals).nx;
		vpc.ny = (*itnormals).ny;
		vpc.nz = (*itnormals).nz;
		vpc.nw = (*itnormals).nw;
		vpc.u = (*ituv).u;
		vpc.v = (*ituv).v;
		ParserVec.push_back(vpc);
	}
	
	return true;
	
		
};
void Parser::Read()
{
	
	
}