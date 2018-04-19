attribute highp vec4 Vertex;
attribute highp vec4 Normal; 
attribute highp vec2 UV;
attribute highp vec4 Tangent;
attribute highp vec4 Binormal;

varying highp vec2 vecUVCoords;
varying highp vec4 Norm;
varying highp vec4 Pos;
varying highp mat3 TBN;

uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;
//uniform highp vec3 PointLight;


void main(){
	vecUVCoords = UV;
	Norm = Normal.xyzw;
	Pos = WVP*Vertex;
	TBN[0] = normalize(World*Tangent).xyz;
	TBN[1] = normalize(World*Binormal).xyz;
	TBN[2] = normalize(World*Norm).xyz;
	gl_Position = Pos;
	//vec3 VectorLight = normalize(PointLight-Pos);
}