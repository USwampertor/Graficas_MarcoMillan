#include <IDVDefs.h>
#include <IDVParser.h>
#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>
#include <string>
#include <iostream>
IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main(int arg, char ** args) {
	/*Parser p;
	std::string link;
	std::cin >> link;
	
	p.Load(link);*/
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