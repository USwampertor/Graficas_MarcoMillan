#include <IDVVideo/IDVBaseDriver.h>

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

IDVBaseDriver*	g_pBaseDriver = 0;

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <IDVUtils/IDVChecker.h>

bool		Texture::LoadTexture(const char *fn) {
	bool found = false;
	std::string path = "Textures/";
	std::string filepath = path + std::string(fn);
	std::ifstream inf(filepath.c_str());
	found = inf.good();
	inf.close();

	int x = 0, y = 0, channels = 0;
	unsigned char *buffer = 0;

	if (!found) {
		buffer = (unsigned char*)g_chkr.pixel_data;
		x = g_chkr.width;
		y = g_chkr.height;
		channels = g_chkr.bytes_per_pixel;
		std::cout << "Texture [" << filepath << "] not found, loading checker" << std::endl;
	}
	else {
		buffer = stbi_load(filepath.c_str(), &x, &y, &channels, 0);
	}

	if (!buffer)
		return false;

	size = x * y*channels;
	bounded = 1;
	this->x = x;
	this->y = y;
	mipmaps = 1;
	this->params = params;

	switch (channels) {
	case 1: {
		props |= TEXT_BASIC_FORMAT::CH_ALPHA;
	}break;
	case 3: {
		props |= TEXT_BASIC_FORMAT::CH_RGB;
	}break;
	case 4: {
		props |= TEXT_BASIC_FORMAT::CH_RGBA;
	}break;
	}

	memcpy(&optname[0], fn, strlen(fn));
	optname[strlen(fn)] = '\0';

	LoadAPITexture(buffer);
	if (found) {
		stbi_image_free(buffer);
	}

	return true;
}

void Texture::DestroyTex() {
	DestroyAPITexture();
}

bool IDVShaderBase::CreateShader(std::string src_vs, std::string src_fs, unsigned int sig) {

	std::string Defines = "";

	bool LinearDepth = true;

	#if VDEBUG_NO_LIGHT
	Defines += "#define NO_LIGHT\n\n";
	#endif

	if (sig&IDVSig::HAS_NORMALS)
		Defines += "#define USE_NORMALS\n\n";
	if (sig&IDVSig::HAS_TEXCOORDS0)
		Defines += "#define USE_TEXCOORD0\n\n";
	if (sig&IDVSig::HAS_TEXCOORDS1)
		Defines += "#define USE_TEXCOORD1\n\n";
	if (sig&IDVSig::HAS_TANGENTS)
		Defines += "#define USE_TANGENTS\n\n";
	if (sig&IDVSig::HAS_BINORMALS)
		Defines += "#define USE_BINORMALS\n\n";
	if (sig&IDVSig::DIFFUSE_MAP)
		Defines += "#define DIFFUSE_MAP\n\n";
	if (sig&IDVSig::SPECULAR_MAP)
		Defines += "#define SPECULAR_MAP\n\n";
	if (sig&IDVSig::GLOSS_MAP)
		Defines += "#define GLOSS_MAP\n\n";
	if (sig&IDVSig::NORMAL_MAP)
		Defines += "#define NORMAL_MAP\n\n";
	if (sig&IDVSig::REFLECT_MAP)
		Defines += "#define REFLECT_MAP\n\n";
	
	
	Defines += "#define lowp \n\n";
	Defines += "#define mediump \n\n";
	Defines += "#define highp \n\n";


//	cout << "Compiling with the following signature[ " << Defines << endl << "]" << endl;

	src_vs = Defines + src_vs;
	src_fs = Defines + src_fs;
	this->Sig = sig;
	return CreateShaderAPI(src_vs, src_fs, sig);
}
