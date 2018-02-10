#include <IDVParser.h>
#include <IDVMath.h>
#include <IDVDefs.h>
#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>
#include <string>
#include <iostream>
IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main(int arg, char ** args) {
	
	/*XMATRIX44 alfa(3, 3, 4, 1, 2, 1, 3, 1, 4, 3, 2, 1, 1, 1, 1, 1);
	XMATRIX44 beta(2, 3, 1, 4, 5, 6, 2, 3, 1, 5, 3, 2, 1, 1, 1, 1);
	XMATRIX44 test;
	alfa *= beta;
	PrintMatrix(alfa);
	std::cout << std::endl;
	XMatTranspose(test,alfa);
	PrintMatrix(test);*/

	XMATRIX44 Position, RotationX, RotationY, RotationZ, MScale, Projection;
	XMatTranslation(Position, 15.0f, -5.0f, 0.0f);
	XMatRotationXLH(RotationX,Deg2Rad(90.0f));
	XMatRotationYLH(RotationY, Deg2Rad(15.0f));
	XMatRotationZLH(RotationZ, Deg2Rad(120.0f));
	XMatScaling(MScale, 1.1f, 1.1f, 1.1f);
	XMatPerspectiveLH(Projection, Deg2Rad(60.0f), 1280.0f / 720.0f, 1.0f, 10000.0f);
	XMATRIX44 Final = Projection*MScale*RotationX*RotationY*RotationZ*Position;
	XMATRIX44 test = Projection*MScale*Position;
	PrintMatrix(test);

 	PrintFromLibrary();
	
	g_pApplication = new IDVTestApplication();
	g_pWindow = new IDVWin32Manager((IDVBaseApplication*)g_pApplication);
	g_pWindow->InitGlobalVars();
	g_pWindow->OnCreateApplication();

	//g_pWindow->UpdateApplication();

	g_pWindow->OnDestroyApplication();

	delete g_pWindow;
	delete g_pApplication;

	return 0;
}