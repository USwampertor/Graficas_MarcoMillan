uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;

varying highp vec2 vecUVCoords;
varying highp vec4 hNormal;
varying highp vec4 Pos;
varying highp vec4 hTangent;
varying highp vec4 hBinormal;

uniform mediump sampler2D tex0;
uniform mediump sampler2D tex1;
uniform highp vec4 LightPositions;

void main(){
	highp vec3 TexColor  = texture2D(tex0, vecUVCoords).xyz;
	highp vec3 TexNormal = texture2D(tex1, vecUVCoords).xyz;
	TexNormal.xyz = TexNormal.xyz * 2.0 - 1.0;
	TexNormal = normalize(TexNormal);
	TexNormal.g = -TexNormal.g;
	highp vec3 Tangent  = normalize(hBinormal);
	highp vec3 Binormal = normalize(hTangent);
	highp vec3 _Normal = normalize(hNormal);
	
	highp vec4 LightVec = normalize(LightPositions-Pos);
	highp float Att = clamp(dot(LightVec,_Normal),0.0,1.0);
	highp vec3 color = Att*TexColor;
	highp mat3 TBN = mat3(Tangent,Binormal,_Normal);
	highp vec3 Normal = normalize(TBN*TexNormal);
	gl_FragColor = vec4(color, 1.0);
}

