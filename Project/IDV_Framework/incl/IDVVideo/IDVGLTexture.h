#ifndef IDV_GLTEXTURE
#define IDV_GLTEXTURE

#include <IDVVideo\IDVBaseDriver.h>

class GLTexture : public Texture {
public:
	GLTexture() {}
	virtual ~GLTexture() {}
	void	SetTextureParams();
	void	GetFormatBpp(unsigned int &props, unsigned int &glFormat, unsigned int &bpp);

	void	LoadAPITexture(unsigned char* buffer);
	void	LoadAPITextureCompressed(unsigned char* buffer);
	void	DestroyAPITexture();
};

#endif
