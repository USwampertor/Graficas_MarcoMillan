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

void main(){
	highp vec3 TexColor  = texture2D(tex0, vecUVCoords).xyz;
	highp vec3 TexNormal = texture2D(tex1, vecUVCoords).xyz;
	TexNormal.xyz = TexNormal.xyz * 2.0 - 1.0;
	TexNormal = normalize(TexNormal);
	highp mat3 TBN = mat3(normalize(hBinormal),normalize(hTangent),normalize(hNormal));
	highp vec3 Normal = normalize(TBN*TexNormal);
	gl_FragColor = vec4(Normal, 1.0);
}

