attribute highp vec4 Vertex;
attribute highp vec4 Normal; 
attribute highp vec2 UV;


varying highp vec2 vecUVCoords;
varying highp vec3 Norm;
varying highp vec4 Pos;

uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;

void main(){
	vecUVCoords = UV;	
	Norm = Normal.xyz;
	Pos = WVP*Vertex;
	gl_Position = Pos;
}