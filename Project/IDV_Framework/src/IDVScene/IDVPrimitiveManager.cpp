#include <IDVScene/IDVPrimitiveManager.h>
#include <IDVScene/IDVGLQuad.h>
#include <IDVScene/IDVD3DQuad.h>
#include <IDVScene/IDV3DMesh.h>
#include <IDVScene/IDVGLMesh.h>
#include <string>
IDVPrimitiveBase*	IDVPrimitiveManager::GetPrimitive(unsigned int index) {
	if (index >= primitives.size())
		return 0;

	return primitives[index];
}

int IDVPrimitiveManager::CreateQuad() {
	IDVPrimitiveBase *primitive = 0;

	if(this->SelectedApi==IDVAPI::OPENGL)
		primitive = new IDVGLQuad();
	else
		primitive = new IDVD3DQuad();

	primitive->Create();
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}
int IDVPrimitiveManager::CreateMesh()
{
	IDVPrimitiveBase *primitive = 0;

	if (this->SelectedApi == IDVAPI::OPENGL)
		primitive = new GLMesh();
	else
		primitive = new D3DXMesh();
	std::string link = "Models/NuCroc.X ";
	primitive->Create(link);
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}
void IDVPrimitiveManager::SetSceneProps(IDVSceneProps *p) {
	for (unsigned int i = 0; i < primitives.size(); i++) {
		primitives[i]->SetSceneProps(p);
	}
}

void IDVPrimitiveManager::DrawPrimitives() {
	for(unsigned int i=0;i<primitives.size();i++){
		primitives[i]->Draw(0,&(*pVP).m[0][0]);
	}
}

void IDVPrimitiveManager::DestroyPrimitives() {
	for (unsigned int i = 0; i < primitives.size(); i++) {
		primitives[i]->Destroy();
		delete primitives[i];
	}
	primitives.clear();
}
