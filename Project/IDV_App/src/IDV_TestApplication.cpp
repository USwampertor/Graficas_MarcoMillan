#include <IDV_TestApplication.h>
#include <stdio.h>
#include <IDVMath.h>
#include <IDVUtils/Timer.h>
void IDVTestApplication::InitVars() 
{
	mainCamera.Init(XVECTOR3(0.0f, 1.0f, -10.0f), Deg2Rad(100.0f), (16.0f / 9.0f), 0.1f, 100000, 1);
	TimeManager.Init();
}

void IDVTestApplication::CreateAssets() {
	IDVPrimitiveMgr = new IDVPrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);
	
	
	int index = IDVPrimitiveMgr->CreateMesh();
	Mesh[0].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &mainCamera.VP);
}

void IDVTestApplication::DestroyAssets() {
	delete IDVPrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {
	
	mainCamera.Update(1.0f);
	TimeManager.Update();
	OnDraw();
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	Mesh[0].Draw();

	m_pWindow->m_pVideoDriver->SwapBuffers();
}

void IDVTestApplication::OnInput() {
	for (int i=0;i< MAXKEYS;i++)
	{
		if (i== 119 && iManager.KeyStates[0][i]==true)
		{
			printf(".");
			TimeManager.GetDTSecs();
			mainCamera.MoveForward(.016f);
		}
	}
}