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
	sceneProp.AddLight(XVECTOR3(0.0f, 1.0f, -8.0f), XVECTOR3(1.0f, 1.0f, 1.0f), true);
	Light = &sceneProp.Lights[0];
	firstFrame = true;
}

void IDVTestApplication::CreateAssets() {
	IDVPrimitiveMgr = new IDVPrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);
	
	std::string alfa = "Models/Scene.X ";
	int index = IDVPrimitiveMgr->CreateMesh(alfa,&sceneProp);
	Mesh[0].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;
	
	alfa = "Models/CerdoNuevo.X ";
	index = IDVPrimitiveMgr->CreateMesh(alfa,&sceneProp);
	Mesh[1].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;

	alfa = "Models/NuCroc.X ";
	index = IDVPrimitiveMgr->CreateMesh(alfa, &sceneProp);
	Mesh[2].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;

	alfa = "Models/NuBatman.X ";
	index = IDVPrimitiveMgr->CreateMesh(alfa, &sceneProp);
	Mesh[3].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;

	alfa = "Models/NuVenomJok.X ";
	index = IDVPrimitiveMgr->CreateMesh(alfa, &sceneProp);
	Mesh[4].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;

	alfa = "Models/Pig.X ";
	index = IDVPrimitiveMgr->CreateMesh(alfa, &sceneProp);
	Mesh[5].CreateInstance(IDVPrimitiveMgr->GetPrimitive(index), &activeCamera->VP);
	instancesInScene++;
	IDVPrimitiveMgr->SetSceneProps(&sceneProp);

	
}

void IDVTestApplication::DestroyAssets() {
	delete IDVPrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {
	
	TimeManager.Update();
	deltaTime = TimeManager.GetDTSecs();
	OnInput();
	Mesh[1].Position.m42 = 5.0f;
	Mesh[1].ScaleAbsolute(4.0f);
	Mesh[1].RotateXAbsolute(0.0f);
	Mesh[1].RotateZAbsolute(90.0f);
	Mesh[1].RotateYAbsolute(90.0f);
	Mesh[1].Update();
	Mesh[2].Position.m41 = 15.0f;
	Mesh[2].ScaleAbsolute(.5f);
	Mesh[2].Update();
	Mesh[3].Position.m41 = 30.0f;
	Mesh[3].ScaleAbsolute(.5f);
	Mesh[3].Update();
	Mesh[4].Position.m41 = 45.0f;
	Mesh[4].ScaleAbsolute(.5f);
	Mesh[4].Update();

	activeCamera->Update(deltaTime);
	Mesh[5].ScaleAbsolute(1.0f);
	Mesh[5].Position.m41 = Light->Position.x;
	Mesh[5].Position.m42 = Light->Position.y;
	Mesh[5].Position.m43 = Light->Position.z;

	Mesh[5].Update();

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


	if (iManager.PressedKey(T800K_UP))
		Light->Position.y += 10.0 * deltaTime;

	if (iManager.PressedKey(T800K_DOWN))
		Light->Position.y -= 10.0 * deltaTime;

	if (iManager.PressedKey(T800K_LEFT))
		Light->Position.x -= 10.0 * deltaTime;

	if (iManager.PressedKey(T800K_RIGHT))
		Light->Position.x += 10.0 * deltaTime;

	if (iManager.PressedKey(T800K_KP1))
		Light->Position.z -= 10.0 * deltaTime;

	if (iManager.PressedKey(T800K_KP2))
		Light->Position.z += 10.0 * deltaTime;
	float yaw = 0.1f*static_cast<float>(iManager.xDelta);
	float pitch = 0.1f*static_cast<float>(iManager.yDelta);
	activeCamera->MovePitch(Deg2Rad(pitch));
	activeCamera->MoveYaw(Deg2Rad(yaw));
	
}