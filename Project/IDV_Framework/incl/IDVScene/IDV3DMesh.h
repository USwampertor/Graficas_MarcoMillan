#ifndef IDV_QUAD_D3D_H
#define IDV_QUAD_D3D_H

//#include <d3dx9math.h>

#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
#include <IDVMath.h>
#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>

class D3DXMesh : public PrimitiveBase {
public:
	struct Vert {
		float x, y, z, w;
		float u, v;
	};
	
	struct CBuffer {
		XMATRIX44 WVP;
		XMATRIX44 World;
		XMATRIX44 WorldView;
	};

	D3DXMesh() {

	}

	void Create();
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;
	ComPtr<ID3D11SamplerState>  pSampler;

	CBuffer			CnstBuffer;
	Vert			vertices[4];
	unsigned short	indices[6];

	XMATRIX44		transform;
};

#endif