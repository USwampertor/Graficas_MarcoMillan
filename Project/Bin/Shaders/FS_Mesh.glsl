uniform highp mat4 WVP;
uniform highp mat4 World;
uniform highp mat4 WorldView;
uniform highp vec4 LightPositions;
uniform highp vec4 CamPos;

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
	TexNormal.g = -TexNormal.g;
	highp vec3 Tangent  = normalize(hBinormal);
	highp vec3 Binormal = normalize(hTangent);
	highp vec3 _Normal = normalize(hNormal);
	
	highp vec4 LightVec = normalize(LightPositions-Pos);
	highp mat3 TBN = mat3(Tangent,Binormal,_Normal);
	highp vec3 Normal = normalize(TBN*TexNormal);
	highp float Att = clamp(dot(LightVec,Normal),0.0,1.0);
	
	highp vec4 Specular= vec4(1.0,1.0,1.0,1.0);
	highp vec4 eyevec = normalize(CamPos - Pos);
	//Phong
	//highp vec4 reflective = (normalize(reflect(LightVec.xyz,Normal)),0.0);	
	//float spec = dot(reflective,eyevec);
	//Blinn
	highp vec4 reflective = normalize(LightVec+eyevec);
	float spec = dot(-reflective,Normal);
	//
	spec = pow(spec,2.0);
	spec *= Att;
	Specular *=spec;
	////Specular *= Specularmap;
	
	highp vec3 color = Att*TexColor;
	color += (Specular).xyz;
	gl_FragColor = vec4(color, 1.0);
}

