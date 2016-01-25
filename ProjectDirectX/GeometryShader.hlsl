#include "ShaderLibrary.hlsli"

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

[maxvertexcount(3)]
void main(
	triangle GS_IN input[3] : SV_POSITION, 
	inout TriangleStream< PS_IN > outputStream
)
{
	for (uint i = 0; i < 3; i++)
	{
		PS_IN element;
		element.Pos = mul(input[i].Pos, mul(worldMatrix, mul(viewMatrix, projectionMatrix)));
		element.Color = input[i].Color;
		outputStream.Append(element);
	}
	outputStream.RestartStrip();
}