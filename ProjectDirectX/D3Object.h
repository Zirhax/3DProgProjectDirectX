#ifndef _D3OBJECT_H_
#define _D3DOBJECT_H_

#include <d3d11.h>
#include "SimpleMath.h"
#include "StructLibrary.h"
#include "TextureObject.h"
#include <fstream>
using namespace std;

class D3Object
{
private:

public:
	D3Object();
	D3Object(const D3Object& original);
	~D3Object();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFileName);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);	//Move model geometry to device context / Graphicscard
#pragma region
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
#pragma endregion getters
};

#endif