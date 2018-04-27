cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
	float4 LightPositions;
	float4 CamPos;
}

struct VS_INPUT{
    float4 position : POSITION;
#ifdef USE_NORMALS
	float4 normal   : NORMAL;
#endif
#ifdef USE_TANGENTS
	float4 tangent  : TANGENT;
#endif
#ifdef USE_BINORMALS
	float4 binormal : BINORMAL;
#endif
#ifdef USE_TEXCOORD0
    float2 texture0 : TEXCOORD;
#endif
};

struct VS_OUTPUT{
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

VS_OUTPUT VS( VS_INPUT input ){
    VS_OUTPUT OUT;
    OUT.hposition = mul(WVP,input.position);
	OUT.wposition = mul(World,input.position);
	float3x3 WorldRot = (float3x3)World;
#ifdef USE_NORMALS
	OUT.hnormal   = float4(mul(WorldRot,input.normal.xyz),1.0);
#endif
#ifdef USE_TANGENTS
	OUT.htangent  = float4(mul(WorldRot,input.tangent.xyz),1.0);
#endif
#ifdef USE_BINORMALS
	OUT.hbinormal = float4(mul(WorldRot,input.binormal.xyz),1.0);
#endif
#ifdef USE_TEXCOORD0
    OUT.texture0  = input.texture0;
#endif
	return OUT;
}

