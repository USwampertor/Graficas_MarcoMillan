#ifndef IDV_SCENEPROPS_H
#define IDV_SCENEPROPS_H

#include <d3dx9math.h>
#include <IDVMath.h>
#include <vector>
#include <IDVUtils/Camera.h>
struct IDVLight{
	XVECTOR3 Position;
	XVECTOR3 Color;
	int		 Type;
	int		 Enabled;
};

struct IDVSceneProps{
	IDVSceneProps() : ActiveCamera(0) , ActiveLights(1), ActiveLightCamera(0), ActiveGaussKernel(0), Exposure(0.3f) , BloomFactor(1.1f) {}

	void	AddLight(XVECTOR3 Pos, XVECTOR3 Color,bool enabled);
	void	AddCamera(Camera*);
	void	RemoveLight(unsigned int index);
	void	SetLightPos(unsigned int index, XVECTOR3);

	std::vector<IDVLight>	   Lights;
	std::vector<Camera*>			pCameras;
	XVECTOR3			AmbientColor;

	int ActiveCamera;
	int	ActiveLights;
	int ActiveLightCamera;
	int ActiveGaussKernel;
	
	// HDR
	float	Exposure;
	float	BloomFactor;
};

#endif
