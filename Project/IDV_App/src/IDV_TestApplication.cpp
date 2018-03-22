#include <IDV_TestApplication.h>
#include <stdio.h>
#include <IDVMath.h>
void IDVTestApplication::InitVars() {
	
}

void IDVTestApplication::CreateAssets() {
	XMATRIX44 VP;
	
	IDVPrimitiveMgr = new IDVPrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);

	//int index = PrimitiveMgr->CreateQuad();
	int index = IDVPrimitiveMgr->CreateMesh();
	QuadInst.CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &VP);
}

void IDVTestApplication::DestroyAssets() {
	delete IDVPrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {

	OnDraw();
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	QuadInst.Draw();

	m_pWindow->m_pVideoDriver->SwapBuffers();
}

void IDVTestApplication::OnInput() {

}