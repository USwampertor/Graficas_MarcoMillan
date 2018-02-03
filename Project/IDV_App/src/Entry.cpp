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
	
	XMATRIX44 alfa(3, 3, 4, 1, 2, 1, 3, 1, 4, 3, 2, 1, 1, 1, 1, 1);
	XMATRIX44 beta(2, 3, 1, 4, 5, 6, 2, 3, 1, 5, 3, 2, 1, 1, 1, 1);
	XMATRIX44 test;
	alfa *= beta;
	PrintMatrix(alfa);
	std::cout << std::endl;
	XMatTranspose(test,alfa);
	PrintMatrix(test);



	PrintFromLibrary();
	
	g_pApplication = new IDVTestApplication();
	g_pWindow = new IDVWin32Manager((IDVBaseApplication*)g_pApplication);
	g_pWindow->InitGlobalVars();
	g_pWindow->OnCreateApplication();

	g_pWindow->UpdateApplication();

	g_pWindow->OnDestroyApplication();

	delete g_pWindow;
	delete g_pApplication;

	return 0;
}