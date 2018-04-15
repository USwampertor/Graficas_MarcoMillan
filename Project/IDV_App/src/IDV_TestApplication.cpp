#include <IDV_TestApplication.h>
#include <stdio.h>
#include <IDVMath.h>
#include <IDVUtils/Timer.h>
void IDVTestApplication::InitVars() 
{
	TimeManager.Init();
	TimeManager.Update();
	srand((unsigned int)TimeManager.GetDTSecs());
	mainCamera.Init(XVECTOR3(0.0f, 1.0f, -10.0f), Deg2Rad(90.0f), (16.0f / 9.0f), 0.1f, 100000, 1);
	mainCamera.Update(0.0f);
	activeCamera = &mainCamera;
	sceneProp.AddCamera(activeCamera);
	firstFrame = true;
}

void IDVTestApplication::CreateAssets() {
	IDVPrimitiveMgr = new IDVPrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);
	
	std::string alfa = "Models/Scene.X ";
	int index = IDVPrimitiveMgr->CreateMesh(alfa);
	Mesh[0].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;
	/*alfa = "Models/Pig.X ";
	index = IDVPrimitiveMgr->CreateMesh(alfa);
	Mesh[1].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;*/

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
	for (int i = 0; i < instancesInScene; i++)
	{
		Mesh[i].Draw();
	}
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

	if (iManager.PressedKey(T800K_q))
		activeCamera->MoveUp(deltaTime);

	if (iManager.PressedKey(T800K_e))
		activeCamera->MoveDown(deltaTime);

	if (iManager.PressedKey(T800K_z))
		activeCamera->TurnRight(deltaTime);

	if (iManager.PressedKey(T800K_c))
		activeCamera->TurnLeft(deltaTime);

	if (iManager.PressedKey(T800K_r))
		activeCamera->TurnUp(deltaTime);

	if (iManager.PressedKey(T800K_f))
		activeCamera->TurnDown(deltaTime);

	float yaw = 0.01f*static_cast<float>(iManager.xDelta);
	float pitch = 0.01f*static_cast<float>(iManager.yDelta);
	activeCamera->MovePitch(Deg2Rad(pitch));
	
}