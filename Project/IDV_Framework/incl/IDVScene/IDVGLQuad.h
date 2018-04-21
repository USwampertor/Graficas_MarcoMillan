#ifndef IDV_QUAD_GL_H
#define IDV_QUAD_GL_H

#include <d3dx9math.h>
#include <IDVMath.h>
#include <GL/glew.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>

class IDVGLQuad : public IDVPrimitiveBase{
public:
	struct Vert {
		float x,y,z,w;
		float u,v;
	};

	IDVGLQuad(){}
	void Create();
	inline void Create(std::string) {};
	void Create(char *){}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	Vert			vertices[8];
	unsigned short	indices[36];
	unsigned int	VB;
	unsigned int	IB;
	XMATRIX44		transform;
	int			 TexId;
	Texture		*pTexture;
};

#endif
