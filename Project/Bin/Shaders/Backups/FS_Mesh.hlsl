cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
	float4 LightPositions;
	float4 CamPos;
}

SamplerState SS;
Texture2D tex0 : register(t0);
#ifdef NORMAL_MAP
Texture2D tex1 : register(t1);
#endif

struct VS_OUTPUT{
	float4 wposition : TEXCOORD1;
    float4 hposition : SV_POSITION;
#ifdef USE_NORMALS
	float4 hnormal   : NORMAL;
#endif
#ifdef USE_TANGENTS
	float4 htangent  : TANGENT;
#endif
#ifdef USE_BINORMALS
	float4 hbinormal : BINORMAL;
#endif
#ifdef USE_TEXCOORD0
    float2 texture0  : TEXCOORD;
#endif
	float4 wposition : TEXCOORD1;
};


float4 FS( VS_OUTPUT input ) : SV_TARGET {
	
	float4 Tan = normalize(input.hbinormal);
	float4 Bin = normalize(input.htangent);
	float4 Norm = normalize(input.hnormal);
	float4 texcolor = tex0.Sample(SS,input.texture0);
	float4 texnormal = tex1.Sample(SS,input.texture0);
	texnormal = texnormal*2.0-1.0;
	texnormal = normalize(texnormal);
	texnormal.g = -texnormal.g;
	
	float4 lightvec = normalize(LightPositions-input.wposition);
	float3x3 TBN= float3x3(Tan.xyz,Bin.xyz,Norm.xyz);
	float4 Normal = float4(normalize(mul(texnormal.xyz,TBN)),1.0);
	float att = clamp(dot(lightvec,Normal),0.0,1.0);
	
	float4 Specular = float4(1.0,1.0,1.0,1.0);
	float4 eyevec = normalize(CamPos-input.wposition);
	////Phong
	//float4 reflective = normalize(reflect(lightvec,Normal));
	//float spec = dot(reflective,eyevec);
	////Blinn
	float4 reflective = normalize(lightvec+eyevec);
	float spec = dot(-reflective,Normal);
	//
	spec = pow(spec,2.0);
	spec*=att;
	Specular *= spec;
	////Specular *= Specularmap
	
	float4 color = att*texcolor;
	color += Specular;
	return color;
}


