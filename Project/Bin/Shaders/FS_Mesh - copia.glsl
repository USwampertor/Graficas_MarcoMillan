uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;

varying highp vec2 vecUVCoords;
varying highp vec4 Norm;
varying highp vec4 Pos;
varying highp mat3 TBN;

uniform mediump sampler2D tex0;

void main(){
	highp vec3 TexNormal = normalize(2.0f * texture2D(tex0, vecUVCoords).xyz - 1.0f).xyz;
	highp vec3 Normal = normalize(TBN*Norm.xyz);
	gl_FragColor = highp(Normal,1.0f);
}

