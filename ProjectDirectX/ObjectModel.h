#ifndef _OBJECTMODEL_H_
#define _OBJECTMODEL_H_
#include <d3d11.h>
#include "SimpleMath.h"
#include "StructLibrary.h"
class ObjectModel
{
private:
	//Remember that the bufferstructure is defined using the buffer-description at creation.
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

	int m_vertexCount, m_indexCount;

	//Handles the initialization and clean-up of our vertex & index buffer
	bool InitializeBuffers(ID3D11Device* device);
	void CleanBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
public:
	ObjectModel();
	ObjectModel(const ObjectModel& original);
	virtual ~ObjectModel();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);	//Move model geometry to device context / Graphicscard
#pragma region
	int GetIndexCount();
#pragma endregion getters
};
#endif
