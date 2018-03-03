#include <string>
#include <vector>
#ifndef IDV_Parser
#define IDV_Paser
void PrintFromLibrary();
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
		float x, y, z, w=0, u, v;

	};
	struct uv
	{
		float u, v;
	};
	struct normals
	{
		float nx, ny, nz, nw;
	};

	std::vector<vertex*> ParserVec;
	std::vector<normals*>ParserNorm;
	std::vector<unsigned short>ParserIndex;
};
#endif
