attribute highp vec4 Vertex;
attribute highp vec4 Normal; 
attribute highp vec2 UV;
attribute highp vec4 Tangent;
attribute highp vec4 Binormal;

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
	hTangent  =  vec4(WorldRot*Tangent.xyz,1.0);
	hBinormal =  vec4(WorldRot*Binormal.xyz,1.0);
	hNormal   =  vec4(WorldRot*Normal.xyz,1.0);
	gl_Position = WVP*Vertex;
}