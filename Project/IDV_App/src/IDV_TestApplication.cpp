#include <IDV_TestApplication.h>
#include <stdio.h>
#include <IDVMath.h>
#include <IDVUtils/Timer.h>
void IDVTestApplication::InitVars() 
{
	TimeManager.Init();
	TimeManager.Update();
	srand((unsigned int)TimeManager.GetDTSecs());
	mainCamera.Init(XVECTOR3(0.0f, 1.0f, -10.0f), Deg2Rad(100.0f), (16.0f / 9.0f), 0.1f, 100000, 1);
	mainCamera.Update(0.0f);
	activeCamera = &mainCamera;
	sceneProp.AddCamera(activeCamera);
	firstFrame = true;
}

void IDVTestApplication::CreateAssets() {
	IDVPrimitiveMgr = new IDVPrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);
	
	
	int index = IDVPrimitiveMgr->CreateMesh();
	Mesh[0].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	
	IDVPrimitiveMgr->SetSceneProps(&sceneProp);

}

void IDVTestApplication::DestroyAssets() {
	delete IDVPrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {
	
	TimeManager.Update();
	deltaTime = TimeManager.GetDTSecs();
	OnInput();
	activeCamera->Update(deltaTime);
	
	

	OnDraw();
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	Mesh[0].Draw();

	m_pWindow->m_pVideoDriver->SwapBuffers();
	firstFrame = false;
}

void IDVTestApplication::OnInput() {
	if (iManager.PressedKey(T800K_w))
		activeCamera->MoveForward(deltaTime);
	

	if (iManager.PressedKey(T800K_s)) 
		activeCamera->MoveBackward(deltaTime);

	if (iManager.PressedKey(T800K_a))
		activeCamera->StrafeLeft(deltaTime);

	if (iManager.PressedKey(T800K_d))
		activeCamera->StrafeRight(deltaTime);

	float yaw = 0.005f*static_cast<float>(iManager.xDelta);
	activeCamera->MoveYaw(Deg2Rad(yaw));
	
}