#ifndef IDV_MESH_GL_H
#define IDV_MESH_GL_H


#include <IDVMath.h>
#include <GL/glew.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>
#include <IDVParser.h>
class GLMesh : public PrimitiveBase {
public:
	struct Vert {
		float x, y, z, w;
		float u, v;
	};

	GLMesh() {}
	void Create();
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	Vert			vertices[4];
	unsigned short	indices[6];
	unsigned int	VB;
	unsigned int	IB;
	XMATRIX44		transform;
	Parser			MeshParser;
};

#endif
