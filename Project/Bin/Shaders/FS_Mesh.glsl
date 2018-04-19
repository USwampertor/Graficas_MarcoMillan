uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;

varying highp vec2 vecUVCoords;
varying highp vec4 Norm;
varying highp vec4 Pos;
varying highp mat3 TBN;

uniform mediump sampler2D tex0;
uniform mediump sampler2D tex1;

void main(){
	highp vec3 TexNormal = normalize(2.0f * texture2D(tex1, vecUVCoords).xyz - 1.0f).xyz;
	highp vec3 TexColor = texture2D(tex0, vecUVCoords).xyz;
	highp vec3 Normal = normalize(TBN*TexNormal);
	gl_FragColor = highp vec4(TexNormal,1.0f);
}

