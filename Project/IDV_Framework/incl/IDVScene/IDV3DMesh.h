#ifndef IDV_MESH_D3D_H
#define IDV_MESH_D3D_H


#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;


#include<vector>
#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
#include <IDVMath.h>
#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>
#include <IDVParser.h>
#include <map>
class D3DXMesh : public IDVPrimitiveBase {
public:
	
	struct CBuffer {
		XMATRIX44 WVP;
		XMATRIX44 World;
		XMATRIX44 WorldView;
		XVECTOR3 LightPositions;
	};
	struct SubsetInfo {
		
		ComPtr<ID3D11Buffer>		IB;
	};
	struct MeshInfo {
		ComPtr<ID3D11Buffer>		VB;
		ComPtr<ID3D11Buffer>		IB;
		std::vector <SubsetInfo>    SubSets;
	};

	D3DXMesh() {

	}
	inline void Create() {};
	void Create(std::string link);
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;
	ComPtr<ID3D11SamplerState>  pSampler;

	std::vector<MeshInfo>		Mesh_Info;

	CBuffer			CnstBuffer;

	XMATRIX44		transform;
	Parser			MeshParser;
	int			 TexId;
	Texture		*pTexture;
	Texture		*pNormal;
	std::map<std::string, Texture*> textureBuffer;
	std::map<std::string, Texture*> normalBuffer;
};

#endif