#include <IDVVideo/IDVGLShader.h>
#include <IDVScene/IDVGLMesh.h>
#include <IDVUtils/IDVUtils.h>
#include <IDVMath.h>
#include <string>
void GLMesh::Create() {
	SigBase = IDVSig::HAS_TEXCOORDS0;

	char *vsSourceP = file2string("Shaders/VS_Mesh.glsl");
	char *fsSourceP = file2string("Shaders/FS_Mesh.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	g_pBaseDriver->CreateShader(vstr, fstr, SigBase);
	std::string link;
	link = "Models/CerdoNuevo.X";
	MeshParser.Load(link);
	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(
		GL_ARRAY_BUFFER, 
		MeshParser.totalvert*sizeof(Parser::vertex), 
		&MeshParser.ParserVec[0], 
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, 
		MeshParser.ParserIndex.size() * sizeof(unsigned short), 
		&MeshParser.ParserIndex[0], 
		GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void GLMesh::Transform(float *t) {
	transform = t;
}

void GLMesh::Draw(float *t, float *vp) {

	if (t)
		transform = t;

	unsigned int sig = SigBase;
	sig |= gSig;
	IDVGLShader * s = dynamic_cast<IDVGLShader*>(g_pBaseDriver->GetShaderSig(sig));

	XMATRIX44 Scale;
	XMATRIX44 View;
	XMATRIX44 Projection;
	XMatViewLookAtLH(View, XVECTOR3(0.0f, 0.0f, -10.0f), XVECTOR3(0.0f, 0.0f, 1.0f), XVECTOR3(0.0f, 1.0f, 0.0f));
	XMatPerspectiveLH(Projection, Deg2Rad(60.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	XMatScaling(Scale, 1.0f, 1.0f, 1.0f);

	XMATRIX44 VP = vp;
	XMATRIX44 WV = vp;
	XMATRIX44 WVP = Scale*View*Projection;
	glUseProgram(s->ShaderProg);
	
	glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);
	glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glEnableVertexAttribArray(s->vertexAttribLoc);
	glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Parser::vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(s->normalAttribLoc);
	glVertexAttribPointer(s->normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Parser::vertex), BUFFER_OFFSET(16));
	glEnableVertexAttribArray(s->uvAttribLoc);
	glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Parser::vertex), BUFFER_OFFSET(32));

	glDrawElements(GL_TRIANGLES, MeshParser.ParserIndex.size(), GL_UNSIGNED_SHORT, 0);
}

void GLMesh::Destroy(){

}
