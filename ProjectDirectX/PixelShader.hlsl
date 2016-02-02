#include "ShaderLibrary.hlsli"

Texture2D c_text : register(t0);
SamplerState samplerType;

//float4 main(PS_IN_TEST input) : SV_TARGET
//{
//	float4 m_color = (float4)0;
//
//	//Sample the pixel color from the color texture
//	m_color = c_text.Sample(samplerType, input.UV);
//	m_color = float4(1.0f, 0.0f, 0.0f, 1.0f);
//	return m_color;
//}

float4 main(PS_IN_UV input) : SV_TARGET
{
	float4 m_color = (float4)0;

	//Sample the pixel color from the color texture
	m_color = c_text.Sample(samplerType, input.UV);
	return m_color;
}

//float4 main(PS_IN input) : SV_TARGET
//{
//	float4 m_color = input.Color;
//	return m_color;
//}