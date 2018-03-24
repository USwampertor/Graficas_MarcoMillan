#include <IDVScene/IDVSceneProp.h>

void	IDVSceneProps::AddLight(XVECTOR3 Pos, XVECTOR3 Color, bool enabled){
	IDVLight l;
	l.Position=Pos;
	l.Color=Color;
	l.Enabled=(int)enabled;
	Lights.push_back(l);
}
void	IDVSceneProps::AddCamera(Camera* cam)
{
	pCameras.push_back(cam);
}
void	IDVSceneProps::RemoveLight(unsigned int index){
	if(index < 0 || index >= Lights.size())
		return;

	Lights.erase(Lights.begin() + index);
}

void	IDVSceneProps::SetLightPos(unsigned int index, XVECTOR3 pos){
	if (index < 0 || index >= Lights.size())
		return;

	Lights[index].Position = pos;
}