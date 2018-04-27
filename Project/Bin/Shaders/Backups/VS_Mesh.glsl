attribute highp vec4 Vertex;
#ifdef USE_NORMALS
attribute highp vec4 Normal;
#endif
#ifdef USE_TEXCOORD0
attribute highp vec2 UV;
#endif
#ifdef USE_TANGENTS
attribute highp vec4 Tangent;
#endif
#ifdef USE_BINORMALS
attribute highp vec4 Binormal;
#endif

varying highp vec4 hTangent;
varying highp vec4 hBinormal;
varying highp vec2 vecUVCoords;
varying highp vec4 hNormal;
varying highp vec4 Pos;


uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;
uniform highp vec4 LightPositions;
uniform highp vec4 CamPos;
void main(){
	vecUVCoords = UV;
	Pos = World*Vertex;
	highp mat3 WorldRot = mat3(World);
#ifdef USE_TANGENTS
	hTangent  =  vec4(WorldRot*Tangent.xyz,1.0);
#endif
#ifdef USE_BINORMALS
	hBinormal =  vec4(WorldRot*Binormal.xyz,1.0);
#endif
#ifdef USE_NORMALS
	hNormal   =  vec4(WorldRot*Normal.xyz,1.0);
#endif
#ifdef NON_LINEAR_DEPTH
	gl_Position = Pos;
#else
	gl_Position = WVP*Vertex;
#endif
}