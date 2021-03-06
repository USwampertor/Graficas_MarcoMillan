#include <stdio.h>
#include <IDVParser.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
Parser::Parser()
{
	txtfile = "TextureFilename";
	nrmfile = "\"normalMap\";";
	effect = "EffectParamString";
	diffuse = "Diffuse";
	dfltstring = "String";
	dfltbreakingpoint = "TextureFilename";
	vertexchecker = "mesh_";
	uvchecker = "tc0";
	normalchecker = "normals";
	tanbinchecker = "DeclData";
	mtrlchecker = "mtls";
	ftest = 0;
	size = 0;
	
	totalmeshes = 0;
}
bool Parser::Load(std::string filename)
{
	std::vector<vertex>::iterator itvert;
	std::vector<uv>::iterator ituv;
	std::vector<normals>::iterator itnormals;
	std::vector<metaobject>::iterator ittan;
	std::vector<metaobject>::iterator itbin;
	
	std::cout << ".";
	std::ifstream mreader;
	mreader.open(filename);
	if (!mreader.is_open())
	{
		std::cout << "couldnt find " << filename << "in specified directory" << std::endl;
		return false;
	}
	std::cout << ".";
	/*mreader.seekg(0, mreader.end);
	size = mreader.tellg();*/
	mreader.seekg(0, mreader.beg);
///vertex finder
	///primero vamos a checar cuantas veces aparece mesh_
	///con eso vamos a saber cuantos meshes tenemos y cuantos vamos a hacer
	///vamos a meter todo en los mismos buffers, pero con los tama�os que obtenemos en cada apartado
	///vamos a definir que tanto debe de ser el buffer de uno y de otro
	while (!mreader.eof())
	{
		mreader >> a;
		if (a == "Mesh")
		{
			mreader >> a;
			b = a.substr(0, 5);
			if (b == vertexchecker)
			{
				totalmeshes++;
			}

		}
	}
	std::cout << ".";
///se supone que aqui como ya checo cuantos mesh_ hay, sabemos cuantos meshes hay y se va a poner a ciclar
	mreader.seekg(0, mreader.beg);
	mreader.seekg(0, mreader.beg);

///me posiciono al principio de nuevo
	for (int index = 0; index < totalmeshes; index++)
	{
		std::vector<uv> uvbuffer;
		std::vector<vertex> vertexbuffer;
		mesh actual;
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
		std::cout << ".";
		mreader >> c >> actual.totalvert >> c;
		for (unsigned int i = 0; i < actual.totalvert; i++)
		{
			vertex vp;
			mreader >> vp.x >> c >> vp.y >> c >> vp.z >> c >> c;
			vertexbuffer.push_back(vp);
		}
		std::cout << ".";
		///index buffer
		mreader >> actual.totalindex >> c;
		for (int index = 0; index<actual.totalindex; index++)
		{
			unsigned short v0, v1, v2;
			mreader >> c >> c >> v0;
			mreader >> c >> v1;
			mreader >> c >> v2;
			mreader >> c >> c;

			actual.MeshIndex.push_back(v0);
			actual.MeshIndex.push_back(v1);
			actual.MeshIndex.push_back(v2);
		}
		std::cout << ".";
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
		std::cout << "x";
		mreader >> c >> actual.totalnormals >> c;
		for (unsigned int i = 0; i < actual.totalnormals; i++)
		{
			normals np;
			mreader >> np.nx >> c >> np.ny >> c >> np.nz >> c >> c;
			actual.MeshNorm.push_back(np);
		}
		std::cout << ".";
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
		mreader >> c >> actual.totaluv >> c;
		for (unsigned int i = 0; i < actual.totaluv; i++)
		{
			uv uvp;
			mreader >> uvp.u >> c >> uvp.v >> c >> c;
			uvbuffer.push_back(uvp);
		}
		std::cout << ".";
		///TanBin buffer
		while (true)
		{
			mreader >> a;
			if (a == tanbinchecker)
			{
				break;
			}
		}
		std::cout << ".";
		mreader >> c >> actual.totalObjects >> c;
		if (actual.totalnormals > 0)
		{
			for (int i = 0; i < actual.totalObjects; i++)
			{
				unsigned short type;
				mreader >> c >> c >> c >> c >> type >> c >> c >> c >> c;
				actual.objectTypes.push_back(type);
			}
			mreader >> actual.totalmeta >> c;
			actual.MeshMeta.resize(actual.totalmeta);
			for (unsigned int i = 0; i < actual.totalvert; i++)
			{
				for (int j = 0; j < actual.totalObjects; j++)
				{
					metaobject meta;
					unsigned int m1, m2, m3;
					mreader >> m1 >> c >> m2 >> c >> m3 >> c;
					float mx = reinterpret_cast<float&>(m1);
					float my = reinterpret_cast<float&>(m2);
					float mz = reinterpret_cast<float&>(m3);
					meta.mx = mx; meta.my = my; meta.mz = mz;
					actual.MeshMeta[j].submeta.push_back(meta);
				}
			}
		}
		std::cout << ".";
		///materials
		while (true)
		{
			mreader >> a;
			if (a == "MeshMaterialList")
			{
				mreader >> a;
				if (a == mtrlchecker)
				{
					break;
				}
			}
		}
		mreader >> c >> actual.matInMesh >> c >> actual.totalMaterial >> c;
		actual.MeshMat.resize(actual.matInMesh);
		int getMatId=-1;
		for (int i = 0; i < actual.totalindex; i++)
		{
			
			mreader >> getMatId >> c;
			actual.MeshMat[getMatId].mtlBuffer.push_back(actual.MeshIndex[(i * 3) + 0]);
			actual.MeshMat[getMatId].mtlBuffer.push_back(actual.MeshIndex[(i * 3) + 1]);
			actual.MeshMat[getMatId].mtlBuffer.push_back(actual.MeshIndex[(i * 3) + 2]);

		}
		std::cout << ".";
		///Mtrls Dflt
		bool cycle = true;
		for (unsigned int i = 0; i < actual.matInMesh; i++)
		{
			std::string normal;
			std::string texture;
			while (cycle)
			{
				mreader >> a;
				if (a == effect)
				{
					mreader >> c >> a;
					if (a == nrmfile)
					{
						char brake = 92;
						mreader >> std::quoted(a);
						if (a.find_last_of(brake) != std::string::npos)
						{
							int last = a.find_last_of(brake);
							normal = a.substr(last+1, a.size() - last);
						}
						else
							normal = a;

						actual.MeshMat[i].usingnormal = true;
					}
				}
				if (a == "EffectParamDWord")
				{
					mreader >> c >> a;
					if (a == "\"Tiled\";")
					{
						mreader >> actual.MeshMat[i].tiledB;
						
					}
					else if (a == "\"NoLighting\";")
					{
						mreader >> actual.MeshMat[i].lightning;
					}
				}

				if (a==txtfile)
				{
					mreader >> a;
					if (a==diffuse)
					{
						cycle = false;
					}
				}
			}
			cycle = true;
			char brake = 92;
			mreader >> c >> std::quoted(a);
			if (a.find_last_of(brake)!= std::string::npos)
			{
				int last = a.find_last_of(brake);
				texture = a.substr(last+1, a.size()-last);
			}
			else
				texture = a;
			actual.txtbuffer.push_back(texture);
			actual.nrmFileBuffer.push_back(normal);
		}
		///Finished to get all shit from a mesh, now going to put all shits in the mesh
		if(actual.MeshMeta.size()>0)
		for (itvert = vertexbuffer.begin(),
			ituv = uvbuffer.begin(),
			ittan = actual.MeshMeta[0].submeta.begin(),
			itbin = actual.MeshMeta[1].submeta.begin(),
			itnormals = actual.MeshNorm.begin();
			itvert != vertexbuffer.end() &&
			ituv != uvbuffer.end() &&
			ittan != actual.MeshMeta[0].submeta.end() &&
			itbin != actual.MeshMeta[1].submeta.end() &&
			itnormals != actual.MeshNorm.end();
			itvert++, ituv++, ittan++, itbin++, itnormals++
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
			vpc.tx = (*ittan).mx;
			vpc.ty = (*ittan).my;
			vpc.tz = (*ittan).mz;
			vpc.bx = (*itbin).mx;
			vpc.by = (*itbin).my;
			vpc.bz = (*itbin).mz;
			vpc.u = (*ituv).u;
			vpc.v = (*ituv).v;
			actual.MeshVec.push_back(vpc);
		}
		else
			for (itvert = vertexbuffer.begin(),
				ituv = uvbuffer.begin(),
				itnormals = actual.MeshNorm.begin();
				itvert != vertexbuffer.end() &&
				ituv != uvbuffer.end() &&
				itnormals != actual.MeshNorm.end();
				itvert++, ituv++, itnormals++
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
				actual.MeshVec.push_back(vpc);
			}


		meshesTotal.push_back(actual);
	}
	
///finished getting all information
	mreader.close();
	
	
	return true;
	
		
};
void Parser::Read()
{
	
	
}