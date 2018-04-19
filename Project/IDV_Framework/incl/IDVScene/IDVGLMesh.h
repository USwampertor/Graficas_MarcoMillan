#ifndef IDV_MESH_GL_H
#define IDV_MESH_GL_H


#include <IDVMath.h>
#include <GL/glew.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>
#include <IDVParser.h>
class GLMesh : public IDVPrimitiveBase {
public:

	struct SubsetInfo {
		unsigned int				Id;
	};
	struct MeshInfo {
		unsigned int		VB;
		unsigned int		IB;
		std::vector <SubsetInfo>    SubSets;
	};

	

	GLMesh() {}
	inline void Create() {};
	void Create(std::string link);
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();
	std::vector<MeshInfo>		Mesh_Info;
	unsigned int	SigBase;
	unsigned int	VB;
	unsigned int	IB;
	XMATRIX44		transform;
	Parser			MeshParser;
	int			 TexId;
	Texture		*pTexture;
	Texture		*pNormal;
	std::map<std::string, Texture*> textureBuffer;
	std::map<std::string, Texture*> normalBuffer;
};

#endif
