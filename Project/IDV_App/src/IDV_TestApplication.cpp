#include <IDV_TestApplication.h>

#include <stdio.h>

void IDVTestApplication::InitVars() {

}

void IDVTestApplication::CreateAssets() {

}

void IDVTestApplication::DestroyAssets() {

}

void IDVTestApplication::OnUpdate() {

	OnDraw();
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	m_pWindow->m_pVideoDriver->SwapBuffers();
}

void IDVTestApplication::OnInput() {

}