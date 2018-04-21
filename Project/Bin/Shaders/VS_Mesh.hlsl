cbuffer ConstantBuffer{
    float4x4 WVP;
	float4x4 World;  
	float4x4 WorldView;
	float4 LightPositions;
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
	OUT.hnormal   = float4(mul(World,input.normal));
	OUT.htangent  = float4(mul(World,input.tangent));
	OUT.hbinormal = float4(mul(World,input.binormal));
    OUT.texture0  = input.texture0;
	return OUT;
}

