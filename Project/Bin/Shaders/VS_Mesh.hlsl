cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
	float4 LightPositions;
	float4 CamPos;
}

struct VS_INPUT{
    float4 position : POSITION;
	float4 normal   : NORMAL;
	float4 tangent  : TANGENT;
	float4 binormal : BINORMAL;
    float2 texture0 : TEXCOORD;
};

struct VS_OUTPUT{
    float4 hposition : SV_POSITION;
	float4 hnormal   : NORMAL;
	float4 htangent  : TANGENT;
	float4 hbinormal : BINORMAL;
    float2 texture0  : TEXCOORD;
	float4 wposition : TEXCOORD1;
};

VS_OUTPUT VS( VS_INPUT input ){
    VS_OUTPUT OUT;
    OUT.hposition = mul(WVP,input.position);
	OUT.wposition = mul(World,input.position);
	float3x3 WorldRot = (float3x3)World;
	OUT.hnormal   = float4(mul(WorldRot,input.normal.xyz),1.0);
	OUT.htangent  = float4(mul(WorldRot,input.tangent.xyz),1.0);
	OUT.hbinormal = float4(mul(WorldRot,input.binormal.xyz),1.0);
    OUT.texture0  = input.texture0;
	return OUT;
}

