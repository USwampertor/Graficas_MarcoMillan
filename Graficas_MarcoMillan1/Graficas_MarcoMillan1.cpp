
// Graficas_MarcoMillan1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;
struct vertex
{
	float x, y, z;

};
int main()
{
	string checker = "mesh_";
	float ftest;
	string a,b,filename;
	string::iterator sit;
	char c,cont;
	vector<vertex*> model;
	vector<vertex*>::iterator mit;
	int size = 0;
	int totalvert = 0;
	bool trigger = false;
	ifstream mreader;
	cout << "Enter file name" << endl << "File must have extension" << endl;
	cin >> filename;
	cout << "Iniciating..." << endl;
	mreader.open(filename);
	if (!mreader.is_open())
	{
		Sleep(20);
		cout << "File cannot be found in default directory..." << endl << "Maybe its somewhere else?" << endl;
		Sleep(200);
		cout << "Closing..." << endl;
		return 0;
	}
	else
	{
		cout << "Loading model"<< filename<<"..." << endl;
		Sleep(500);
		mreader.seekg(0, mreader.end);
		size = mreader.tellg();
		cout << "File size... " << size<<endl;
		mreader.seekg(0, mreader.beg);
		//aqui se posiciona en mesh
		while(true)
		{
			mreader >> a;
			if (a=="Mesh")
			{
				mreader >> a;	
				b = a.substr(0, 5);
				if (b==checker)
				{
					break;
				}

			}
		}
		mreader >> c >> totalvert >> c;
		cout<<endl<<endl<<"Object vertex: " << totalvert << endl;
		//aqui estoy leyendo los valores, mostrandolos y guardandolos en un contenedor vector
		
		for (int i = 0; i < totalvert; i++)
		{
			vertex *p = new vertex;
			mreader >> p->x >> c >> p->y >> c >> p->z >> c >> c;
			cout << "Vertex " << i+1 << ":	x: " << p->x << "	y: " << p->y << "	z: " << p->z << endl;
			if (!trigger)
			{
				cont = _getch();
				if (cont != 13&&cont==32)
				{
					//continuo un vertice
				}
				if (cont == 13)
				{
					trigger = true;
				}
			}
			model.push_back(p);
		}
		mreader.close();
		cout << "All vertex have been loaded into model_vector..." << endl;
		
		Sleep(2000);
		/*for ( mit = model.begin(); mit != model.end(); mit++)
		{
			cout<<"vertice "<<":	x: "<<(*mit)->x << "	y: " << (*mit)->y << "	z: " << (*mit)->z<<endl;
			if (!trigger)
			{
				cont = _getch();
				if (cont != 13 && cont == 32) 
				{
					//continuo un vertice
				}
				if (cont ==13)
				{
					trigger = true;
				}
			}
		}*/

		
	}
    return 0;
}