#pragma once
//#ifndef IDV_Parser
//#define IDV_Paser
#include <string>
#include <vector>
class Parser 
{
public:
	
	Parser();
	bool Load(std::string filename);
	void Read();
	std::string normalchecker, uvchecker, indexchecker, vertexchecker, a, b;
	float ftest;
	char c, cont;
	int size,totalvert,totalnormals,totaluv;
	unsigned short totalindex;
	struct vertex
	{
		vertex() : x(0.0f) , y(0.0f), z(0.0f) , w(1.0f) , 
				   nx(0.0f), ny(1.0f), nz(0.0f), nw(1.0f),
				   u(0.0f) , v(0.0f)
		{}
		float x, y, z, w;
		float nx,ny,nz,nw;
		float u, v;

	};
	struct uv
	{
		float u, v;
	};
	struct normals
	{
		float nx, ny, nz, nw;
	};

	std::vector<vertex> ParserVec;
	std::vector<normals>ParserNorm;
	std::vector<unsigned short>ParserIndex;
};
//#endif
