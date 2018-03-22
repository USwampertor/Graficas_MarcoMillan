#ifndef IDV_BASEDRIVER_H
#define IDV_BASEDRIVER_H

#include <string>
#include <vector>

enum IDVSig {
	// ATTRIBUTES
	HAS_NORMALS		= 0x1,
	HAS_TANGENTS	= 0x2,
	HAS_BINORMALS	= 0x4,
	HAS_TEXCOORDS0	= 0x8,
	HAS_TEXCOORDS1	= 0x10,

	// MAPS
	DIFFUSE_MAP		= 0x20,
	SPECULAR_MAP	= 0x40,
	GLOSS_MAP		= 0x80,
	NORMAL_MAP		= 0x100,
	REFLECT_MAP		= 0x200,
	HEIGHT_MAP		= 0x400,

	// CASES
	USE_NO_LIGHT	= 0x800
};

enum IDVAPI {
	DIRECTX = 0,
	OPENGL
};

class IDVShaderBase {
public:
	IDVShaderBase() : Sig(0) {	}
	bool			CreateShader(std::string src_vs, std::string src_fs, unsigned int sig);
	virtual bool    CreateShaderAPI(std::string src_vs, std::string src_fs, unsigned int sig) = 0;

	unsigned int	Sig;
};


enum TEXT_BASIC_FORMAT {
	CH_ALPHA = 1,
	CH_RGB = 2,
	CH_RGBA = 4
};

enum TEXT_BASIC_PARAMS {
	TILED = 1,
	CLAMP_TO_EDGE = 2,
	MIPMAPS = 4
};

class Texture {
public:
	Texture() :
		size(0),
		props(0),
		params(0),
		x(0),
		y(0),
		id(0),
		bounded(0),
		mipmaps(0)
	{

	}

	virtual ~Texture() {}

	bool			LoadTexture(const char *fn);
	void			DestroyTex();

	virtual void	LoadAPITexture(unsigned char* buffer) = 0;
	virtual void	LoadAPITextureCompressed(unsigned char* buffer) = 0;
	virtual void	DestroyAPITexture() = 0;

	virtual void	SetTextureParams() = 0;
	virtual void	GetFormatBpp(unsigned int &props, unsigned int &format, unsigned int &bpp) = 0;

	char			optname[128];
	unsigned int	size;
	unsigned int	props;
	unsigned int	params;
	unsigned short	x, y;
	unsigned int	id;
	unsigned char	bounded;
	unsigned char	mipmaps;
};

class IDVBaseDriver {
public:
	enum {
		DEPTH_ATTACHMENT = -1,
		COLOR0_ATTACHMENT = 0,
		COLOR1_ATTACHMENT = 1,
		COLOR2_ATTACHMENT = 2,
		COLOR3_ATTACHMENT = 3,
		COLOR4_ATTACHMENT = 4,
		COLOR5_ATTACHMENT = 5,
		COLOR6_ATTACHMENT = 6,
		COLOR7_ATTACHMENT = 7,
	};
	IDVBaseDriver(IDVAPI Selected) {
		SelectedApi = Selected;
	}
	virtual	void	 InitDriver() = 0;
	virtual void	 CreateSurfaces() = 0;
	virtual void	 DestroySurfaces() = 0;
	virtual void	 Update() = 0;
	virtual void	 DestroyDriver() = 0;
	virtual void	 SetWindow(void *window) = 0;
	virtual void	 SetDimensions(int,int) = 0;
	virtual void	 Clear() = 0;
	virtual void	 SwapBuffers() = 0;

	virtual int			CreateShader(std::string src_vs, std::string src_fs, unsigned int sig) = 0;
	virtual IDVShaderBase*	GetShaderSig(unsigned int sig) = 0;
	virtual IDVShaderBase*	GetShaderIdx(int id) = 0;
	virtual void		DestroyShaders() = 0;

	IDVAPI						SelectedApi;
	std::vector<IDVShaderBase*>	Shaders;
};


#ifndef GETDRIVERBASE
extern IDVBaseDriver *g_pBaseDriver;
#define GETDRIVERBASE() g_pBaseDriver
#endif

#endif
