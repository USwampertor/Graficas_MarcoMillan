#include <IDVVideo/IDVGLShader.h>
#include <IDVScene/IDVGLMesh.h>
#include <IDVUtils/IDVUtils.h>
#include <IDVVideo/IDVGLTexture.h>
#include <IDVMath.h>
#include <string>
void GLMesh::Create(std::string link) {
	
	SigBase = IDVSig::HAS_TEXCOORDS0 | IDVSig::HAS_NORMALS;
	char *vsSourceP = file2string("Shaders/VS_Mesh.glsl");
	char *fsSourceP = file2string("Shaders/FS_Mesh.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);
	
	
	MeshParser.Load(link);
	Mesh_Info.reserve(MeshParser.totalmeshes);
	for (int i = 0; i < MeshParser.totalmeshes; i++)
	{
		Parser::mesh pactual = MeshParser.meshesTotal[i];
		MeshInfo tmp;
		g_pBaseDriver->CreateShader(vstr, fstr, SigBase);
		glGenBuffers(1, &tmp.VB);
		glBindBuffer(GL_ARRAY_BUFFER, tmp.VB);
		glBufferData(
			GL_ARRAY_BUFFER, 
			pactual.totalvert *sizeof(Parser::vertex), 
			&pactual.MeshVec[0] , 
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &tmp.IB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp.IB);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, 
			pactual.MeshIndex.size() * sizeof(unsigned short),
			&pactual.MeshIndex[0],
			GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		for (int j = 0; j < pactual.matInMesh; j++)
		{
			SubsetInfo tmp_subset;
			pTexture = new GLTexture;

			TexId = pTexture->LoadTexture(pactual.txtbuffer[j].c_str());

			if (TexId == -1) {
				delete pTexture;
			}
			glGenBuffers(1, &tmp_subset.Id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tmp_subset.Id);
			glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				pactual.MeshMat[j].mtlBuffer.size() * sizeof(unsigned short),
				&pactual.MeshMat[j].mtlBuffer[0],
				GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			tmp.SubSets.push_back(tmp_subset);
			textureBuffer.insert(std::make_pair(pactual.txtbuffer[j], (pTexture)));

		}
		Mesh_Info.push_back(tmp);
	}

}

void GLMesh::Transform(float *t) {
	transform = t;
}

void GLMesh::Draw(float *t, float *vp) {

	if (t)
		transform = t;
	
	for (int i = 0; i < MeshParser.totalmeshes; i++)
	{
		MeshInfo drawinfo = Mesh_Info[i];
		Parser::mesh pactual = MeshParser.meshesTotal[i];
		
		XMATRIX44 Scale;
		XMATRIX44 View;
		XMATRIX44 Projection;
		XMatViewLookAtLH(View, XVECTOR3(0.0f, 1.0f, -10.0f), XVECTOR3(0.0f, 10.0f, 1.0f), XVECTOR3(0.0f, 100.0f, 0.0f));
		XMatPerspectiveLH(Projection, Deg2Rad(100.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
		XMatScaling(Scale, 0.5f, 0.5f, 0.5f);

		XMATRIX44 VP = vp;
		XMATRIX44 WV = vp;
		XMATRIX44 WVP = Scale*View*Projection;

		unsigned int sig = SigBase;
		sig |= gSig;
		IDVGLShader * s = 0;
		
		glBindBuffer(GL_ARRAY_BUFFER, drawinfo.VB);
	
		for (unsigned int j = 0; j < drawinfo.SubSets.size(); j++)
		{
			SubsetInfo subinfo = drawinfo.SubSets[j];
			s = dynamic_cast<IDVGLShader*>(g_pBaseDriver->GetShaderSig(sig));
			
			
			glUseProgram(s->ShaderProg);
			
			glUniformMatrix4fv(s->matWorldUniformLoc, 1, GL_FALSE, &transform.m[0][0]);
			glUniformMatrix4fv(s->matWorldViewProjUniformLoc, 1, GL_FALSE, &WVP.m[0][0]);
			glUniformMatrix4fv(s->matWorldViewUniformLoc, 1, GL_FALSE, &WV.m[0][0]);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subinfo.Id);
			auto it = this->textureBuffer.find(pactual.txtbuffer[j]);
			GLTexture *texgl = dynamic_cast<GLTexture*>(it->second);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texgl->id);
			glUniform1i(s->DiffuseTex_loc, 0);

			glEnableVertexAttribArray(s->vertexAttribLoc);
			glVertexAttribPointer(s->vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Parser::vertex), BUFFER_OFFSET(0));
			glEnableVertexAttribArray(s->normalAttribLoc);
			glVertexAttribPointer(s->normalAttribLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Parser::vertex), BUFFER_OFFSET(16));
			glEnableVertexAttribArray(s->uvAttribLoc);
			glVertexAttribPointer(s->uvAttribLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Parser::vertex), BUFFER_OFFSET(32));

			glDrawElements(GL_TRIANGLES, pactual.MeshMat[j].mtlBuffer.size(), GL_UNSIGNED_SHORT, 0);
		}
		
	}
}

void GLMesh::Destroy(){

}
