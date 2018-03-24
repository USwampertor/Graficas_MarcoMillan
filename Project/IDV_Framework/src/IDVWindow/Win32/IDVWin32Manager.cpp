#include <IDVWindow/IDVWin32Manager.h>

#include <IDVVideo/IDVGLDriver.h>

#include <IDVVideo/IDVD3DXDriver.h>
// SDL
#include <SDL/SDL.h>
// Windows
#include <windows.h>
#include <mmsystem.h>
void IDVWin32Manager::InitGlobalVars() {
	m_pApplication->InitVars();
}

void IDVWin32Manager::OnCreateApplication() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Video initialization failed: %s\n", SDL_GetError());
	}

	SDL_WM_SetCaption("IDV", 0);
	int height = 720;
	int width = 1280;
	if (SDL_SetVideoMode(1280, height, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE) == 0) {
		printf("Video mode set failed: %s\n", SDL_GetError());
	}


//	m_pVideoDriver = new IDVGLDriver();
	m_pVideoDriver = new IDVD3DXDriver();

	m_pVideoDriver->SetDimensions(width, height);

	m_pVideoDriver->SetWindow(0);
	m_pVideoDriver->InitDriver();

	g_pBaseDriver = m_pVideoDriver;

	m_pApplication->CreateAssets();
}

void IDVWin32Manager::OnDestroyApplication() {
	m_pApplication->DestroyAssets();
	m_pVideoDriver->DestroyDriver();
	delete m_pVideoDriver;
	SDL_Quit();
}

void IDVWin32Manager::UpdateApplication() {
	while (m_bAlive) {
		ProcessInput();
		m_pApplication->OnInput();
		m_pApplication->OnUpdate();
		
	}
}

void IDVWin32Manager::ProcessInput() {
	SDL_Event       evento;
	while (SDL_PollEvent(&evento)) {
		switch (evento.type) {
		case SDL_KEYDOWN: 
		{
			if (evento.key.keysym.sym == SDLK_q) 
			{
				m_bAlive = false;
			}
			if (evento.key.keysym.sym == SDLK_w)
			{
				m_pApplication->iManager.KeyStates[0][119] = true;
				printf("going front");
			}
			if (evento.key.keysym.sym == SDLK_a)
			{
				m_pApplication->iManager.KeyStates[0][97] = true;
				printf("going left");
			}
			if (evento.key.keysym.sym == SDLK_s)
			{
				m_pApplication->iManager.KeyStates[0][115] = true;
				printf("going back");
			}
			if (evento.key.keysym.sym == SDLK_d)
			{
				m_pApplication->iManager.KeyStates[0][100] = true;
				printf("going right");
			}
			
		}
		break;

		case SDL_QUIT: {
			m_bAlive = false;
		}break;

		case SDL_KEYUP: 
		{
			if (evento.key.keysym.sym == SDLK_w)
			{
				m_pApplication->iManager.KeyStates[0][119] = false;
				printf("stopping front");
			}
			if (evento.key.keysym.sym == SDLK_a)
			{
				m_pApplication->iManager.KeyStates[0][97] = false;
				printf("stopping left");
			}
			if (evento.key.keysym.sym == SDLK_s)
			{
				m_pApplication->iManager.KeyStates[0][115] = false;
				printf("stopping back");
			}
			if (evento.key.keysym.sym == SDLK_d)
			{
				m_pApplication->iManager.KeyStates[0][100] = false;
				printf("stopping right");
			}
		}
		break;

		case SDL_VIDEORESIZE: {
			printf("New dim %d x %d \n", evento.resize.w, evento.resize.h);
		}break;


		}
	}
}