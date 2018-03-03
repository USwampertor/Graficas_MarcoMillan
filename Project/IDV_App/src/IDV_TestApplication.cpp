#include <IDV_TestApplication.h>
#include <stdio.h>
#include <IDVMath.h>
void IDVTestApplication::InitVars() {

}

void IDVTestApplication::CreateAssets() {
	XMATRIX44 VP;

	PrimitiveMgr = new PrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);

	//int index = PrimitiveMgr->CreateQuad();
	int index = PrimitiveMgr->CreateMesh();
	QuadInst.CreateInstance(PrimitiveMgr->GetPrimitive(index), &VP);
}

void IDVTestApplication::DestroyAssets() {
	delete PrimitiveMgr;
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