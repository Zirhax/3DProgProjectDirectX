#include "ObjectModel.h"





ObjectModel::ObjectModel()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_vertexCount = 0;
	m_indexCount = 0;
}

ObjectModel::ObjectModel(const ObjectModel & original)
{
}


ObjectModel::~ObjectModel()
{
}


//PUBLIC----------------------------------------------------------------------------------
bool ObjectModel::Initialize(ID3D11Device * device)
{
	bool result = true;

	//Initialize the vertex and index buffer
	result = this->InitializeBuffers(device);

	return result;
}

void ObjectModel::Shutdown()
{
	//Release the vertex and index buffers.
	this->CleanBuffers();
	return;
}

void ObjectModel::Render(ID3D11DeviceContext * deviceContext)
{
	this->RenderBuffers(deviceContext);
	return;
}

int ObjectModel::GetIndexCount()
{
	return this->m_indexCount;
}


//PRIVATE----------------------------------------------------------------------------------
bool ObjectModel::InitializeBuffers(ID3D11Device * device)
{
	Vertex* vertices = NULL;
	unsigned long* indices = NULL;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	
	//Set the number of vertices in the vertex array.
	this->m_vertexCount = 4;
	this->m_indexCount = 4;

	//Create buffers and check for successfull completion.
	//Create the vertex array. Fun part :D
	vertices = new Vertex[this->m_vertexCount];
	if (!vertices)
	{
		return false;
	}
	//Create the index array. Not so much fun, but good.
	indices = new unsigned long[this->m_indexCount];
	if (!indices)
	{
		return false;
	}
	//This is where the .obj files and material files will be loaded into the structures and thus subresources
	//Load the vertex data
	vertices[0].position = Vector3(-1.0f, -1.0f, 0.0f);
	vertices[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = Vector3(0.0f, 1.0f, 0.0f);
	vertices[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = Vector3(1.0f, -1.0f, 0.0f);
	vertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

	/*vertices[3].position = Vector3(1.0f, 1.0f, 0.0f);
	vertices[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);*/


	//Load the index data
	indices[0] = 0;	//Bottom left.
	indices[1] = 1; //Top Left.
	indices[2] = 2;	//Bottom right.
	//indices[3] = 3; //Top Right

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * this->m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Create the vertex buffer
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &this->m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Release the vertex array and the index array. the data has been stored in their respective buffer.
	delete[] vertices;
	vertices = NULL;
	delete[] indices;
	indices = NULL;


	return true;
}

void ObjectModel::CleanBuffers()
{
	//Release the vertex buffer
	if (this->m_vertexBuffer != NULL)
	{
		this->m_vertexBuffer->Release();
		this->m_vertexBuffer = NULL;
	}
	//Release the index buffer
	if (this->m_indexBuffer != NULL)
	{
		this->m_indexBuffer->Release();
		this->m_indexBuffer = NULL;
	}

	return;
}

void ObjectModel::RenderBuffers(ID3D11DeviceContext * deviceContext)
{
	unsigned int stride = 0;
	unsigned int offset = 0;

	stride = sizeof(Vertex);

	//Set the vertex buffer for the input assembler.
	deviceContext->IASetVertexBuffers(0, 1, &this->m_vertexBuffer, &stride, &offset);

	//Do the same for the index buffer.
	deviceContext->IASetIndexBuffer(this->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//Actually set the topology
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	return;
}




