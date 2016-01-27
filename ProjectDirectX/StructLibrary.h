#pragma once

#include "SimpleMath.h"
#include <string>
using namespace DirectX::SimpleMath;
struct Vertex
{
	Vector3 position;
	Vector4 color;
};

struct MatrixBufferStruct
{
	Matrix world;
	Matrix view;
	Matrix projection;
};

// input layout (verified using vertex shader)
static const D3D11_INPUT_ELEMENT_DESC inputDescColor[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//The one using a texture
static const D3D11_INPUT_ELEMENT_DESC inputDescUV[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//Shader names
static const char *VERTEXSHADER_NAME = "VertexShader.hlsl", *GEOMETRYSHADER_NAME = "GeometryShader.hlsl", *PIXELSHADER_NAME = "PixelShader.hlsl";
static const WCHAR *VERTEXSHADER_NAME_WCHAR = L"VertexShader.hlsl", *GEOMETRYSHADER_NAME_WCHAR = L"GeometryShader.hlsl", *PIXELSHADER_NAME_WCHAR = L"PixelShader.hlsl";
