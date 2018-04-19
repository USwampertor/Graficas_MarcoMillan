#pragma once
#ifndef IDV_Parser
#define IDV_Paser
#include <string>
#include <vector>
#include <map>
class Parser 
{
public:
	
	Parser();
	void Read();
	bool Load(std::string filename);
	struct vertex
	{
		vertex() : 
			x(0.0f) , y(0.0f), z(0.0f) , w(1.0f) , 
			nx(0.0f), ny(1.0f), nz(0.0f), nw(1.0f),
			tx(0.0f), ty(0.0f), tz(0.0f), tw(1.0f),
			bx(0.0f), by(0.0f), bz(0.0f), bw(1.0f),
				   u(0.0f) , v(0.0f)
		{}
		float x, y, z, w;
		float nx,ny,nz,nw;
		float tx, ty, tz, tw;
		float bx, by, bz, bw;
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
	struct metaobject
	{
		float mx, my, mz;
	};
	struct metasubset
	{
		
		std::vector<metaobject> submeta;
	};
	
	struct matsubset
	{
		//std::map<int, std::string> strBuffer;
		std::vector<unsigned short> mtlBuffer;
	};
	struct mesh
	{
		mesh() : totalvert(0), totalnormals(0), totalindex(0), totaluv(0),totalmeta(0)
		{}
		std::vector<std::string> txtbuffer;
		std::vector<std::string> nrmFileBuffer;
		std::vector<unsigned short> objectTypes;
		std::vector<matsubset> MeshMat;
		std::vector<metasubset>MeshMeta;
		std::vector<vertex> MeshVec;
		std::vector<normals>MeshNorm;
		std::vector<unsigned short> MeshIndex;
		unsigned int 
			totalvert, totalnormals, totaluv,totalmeta,
			totalMaterial;
		unsigned short totalindex, totalObjects,matInMesh;
	};
	std::vector<mesh> meshesTotal;
	std::string
		normalchecker, uvchecker, indexchecker,
		vertexchecker, tanbinchecker, mtrlchecker,
		a, b, dfltbreakingpoint, dfltstring,
		txtfile, nrmfile, diffuse, effect;
	int size, totalmeshes;
	
	float ftest;
	char c, cont;
};
#endif
