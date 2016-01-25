struct VS_IN
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
};

struct GS_IN
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

struct GS_IN_NEW
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

struct PS_IN
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

struct PS_IN_NEW
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float Pad1;
};

SamplerState p_sampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};
