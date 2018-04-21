#include <IDVVideo/IDVGLShader.h>
#include <IDVVideo/IDVGLTexture.h>
#include <IDVScene/IDVGLQuad.h>
#include <IDVUtils/IDVUtils.h>
#include <IDVMath.h>
void IDVGLQuad::Create(){

	pTexture = new GLTexture;

	//TexId = pTexture->LoadTexture("cerdo_D.tga");

	if (TexId == -1) {
		delete pTexture;
	}
	SigBase = IDVSig::HAS_TEXCOORDS0;

	char *vsSourceP = file2string("Shaders/VS_Quad.glsl");
	char *fsSourceP = file2string("Shaders/FS_Quad.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

	vertices[0] = { -.05f,  .05f, -.05f, 1.0f,  0.0f, 0.0f };
	vertices[1] = { -.05f, -.05f, -.05f, 1.0f,  0.0f, 0.5f };
	vertices[2] = {  .05f, -.05f, -.05f, 1.0f,  0.5f, 0.5f };
	vertices[3] = {  .05f,  .05f, -.05f, 1.0f,  0.5f, 0.0f };
	vertices[4] = {  .05f,  .05f,  .05f, 1.0f,  0.5f, 0.0f };
	vertices[5] = {  .05f, -.05f,  .05f, 1.0f,  0.5f, 0.0f };
	vertices[6] = { -.05f, -.05f,  .05f, 1.0f,  0.5f, 0.0f };
	vertices[7] = { -.05f,  .05f,  .05f, 1.0f,  0.5f, 0.0f };

	indices[0] = 2;
	indices[1] = 1;
	indices[2] = 0;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 0;
	indices[6] = 5;
	indices[7] = 2;
	indices[8] = 3;
	indices[9] = 4;
	indices[10] = 5;
	indices[11] = 3;
	indices[12] = 6;
	indices[13] = 5;
	indices[14] = 4;
	indices[15] = 7;
	indices[16] = 6;
	indices[17] = 4;
	indices[18] = 1;
	indices[19] = 6;
	indices[20] = 7;
	indices[21] = 0;
	indices[22] = 1;
	indices[23] = 7;
	indices[24] = 3;
	indices[25] = 0;
	indices[26] = 7;
	indices[27] = 4;
	indices[28] = 3;
	indices[29] = 7;
	indices[30] = 2;
	indices[31] = 1;
	indices[32] = 6;
	indices[33] = 5;
	indices[34] = 2;
	indices[35] = 6;


	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vert), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned short), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void IDVGLQuad::Transform(float *t){
	transform = t;
}

void IDVGLQuad::Draw(float *t, float *vp){

	if (t)
		transform = t;

	unsigned int sig = SigBase;
	sig |= gSig;
	IDVGLShader * s = dynamic_cast<IDVGLShader*>(g_pBaseDriver->GetShaderSig(sig));

	XMATRIX44 VP = vp;
	XMATRIX44 WV = vp;
	
	glUseProgram(s->ShaderProg);

	glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	GLTexture *texgl = dynamic_cast<GLTexture*>(this->pTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texgl->id);
	glUniform1i(s->DiffuseTex_loc, 0);

	glEnableVertexAttribArray(s->vertexAttribLoc);
	glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(s->uvAttribLoc);
	glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(16));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void IDVGLQuad::Destroy(){

}
