#include "ShaderLibrary.hlsli"


cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

GS_IN main(VS_IN input)
{
	GS_IN output = (PS_IN)0;

	output.Pos = float4(input.Pos, 1);
	output.Color = input.Color;

	return output;
}