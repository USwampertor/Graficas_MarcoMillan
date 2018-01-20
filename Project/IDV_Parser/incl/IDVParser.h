#include <string>
#ifndef IDV_Parser
#define IDV_Paser
void PrintFromLibrary();
class Parser 
{
public:
	bool Load(std::string filename);
	Parser();
	std::string checker, a, b;
	float ftest;
	char c, cont;
	int size,totalvert;
	struct vertex
	{
		float x, y, z;

	};
	
};
#endif
