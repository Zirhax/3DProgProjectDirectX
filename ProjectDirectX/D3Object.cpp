#include "D3Object.h"



D3Object::D3Object()
{
}

D3Object::D3Object(const D3Object & original)
{
}


D3Object::~D3Object()
{
}

bool D3Object::Initialize(ID3D11Device* device, char* modelFilename)
{
	return false;
}

void D3Object::Shutdown()
{
}

void D3Object::Render(ID3D11DeviceContext * deviceContext)
{
}

int D3Object::GetIndexCount()
{
	return 0;
}

ID3D11ShaderResourceView * D3Object::GetTexture()
{
	return nullptr;
}

bool D3Object::InitializeBuffers(ID3D11Device *)
{
	return false;
}

void D3Object::ShutdownBuffers()
{
}

void D3Object::RenderBuffers(ID3D11DeviceContext *)
{
}

bool D3Object::LoadTexture(ID3D11Device *, WCHAR *)
{
	return false;
}

void D3Object::ReleaseTexture()
{
}

bool D3Object::LoadModel(char *)
{
	return false;
}

void D3Object::ReleaseModel()
{
}
