#include "ShaderLibrary.hlsli"

float4 main(PS_IN input) : SV_TARGET
{
	float4 m_color = input.Color;
	return m_color;
}