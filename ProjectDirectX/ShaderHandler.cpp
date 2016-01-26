#include "ShaderHandler.h"




ShaderHandler::ShaderHandler()
{
	this->m_vertexShader = NULL;
	this->m_pixelShader = NULL;
	this->m_layout = NULL;
	this->m_matrixBuffer = NULL;
}


ShaderHandler::ShaderHandler(const ShaderHandler & original)
{
}


ShaderHandler::~ShaderHandler()
{
}

//PUBLIC---------------------------------------------------------------------------------------------------------

bool ShaderHandler::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result = false;
	WCHAR* vsName = L"VertexShader.hlsl";
	WCHAR* gsName = L"GeometryShader.hlsl";
	WCHAR* psName = L"PixelShader.hlsl";
	//Initialize the vertex and pixel shaders
	result = this->InitializeShader(device, hwnd, vsName, gsName, psName);
	
	return result;
}

void ShaderHandler::Shutdown()
{
	//Free the memory
	this->FreeMemory();

	return;
}

bool ShaderHandler::Render(ID3D11DeviceContext * deviceContext, int indexCount, MatrixBufferStruct matrices)
{
	bool result = false;

	//Set the shader parameters that we will use when rendering
	result = SetShaderParameters(deviceContext, matrices);
	if (!result)
	{
		return false;
	}

	//Now render the prepared buffers with the shader
	RenderShader(deviceContext, indexCount);

	return result;
}


//PRIVATE---------------------------------------------------------------------------------------------------------


bool ShaderHandler::InitializeShader(ID3D11Device * device, HWND hwnd, WCHAR *vsFilename, WCHAR *gsFilename, WCHAR *psFilename)
{
	HRESULT hResult;
	ID3DBlob* errorMessage = nullptr;
	ID3DBlob* pVS = nullptr;
	ID3DBlob* pGS = nullptr;
	ID3DBlob* pPS = nullptr;
	D3D11_BUFFER_DESC  matrixBufferDesc;
#pragma region
	hResult = D3DCompileFromFile(
		vsFilename,		// filename VERTEXSHADER_NAME_WCHAR
		nullptr,		// optional macros
		nullptr,		// optional include files
		"VS_main",		// entry point
		"vs_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pVS,			// double pointer to ID3DBlob		
		&errorMessage	// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
		);
	if (FAILED(hResult))
	{
		//If it failed to complile we should be able to get the error from the data blob
		if (errorMessage != nullptr)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else	//If it failed but there was nothing in the error blob, then that means the file could not be located
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}
		
		return false;
	}
	

	hResult = D3DCompileFromFile(
		psFilename, // filename
		nullptr,		// optional macros
		nullptr,		// optional include files
		"PS_main",		// entry point
		"ps_4_0",		// shader model (target)
		0,				// shader compile options
		0,				// effect compile options
		&pPS,			// double pointer to ID3DBlob		
		&errorMessage	// pointer for Error Blob messages.
						// how to use the Error blob, see here
						// https://msdn.microsoft.com/en-us/library/windows/desktop/hh968107(v=vs.85).aspx
		);
	if (FAILED(hResult))
	{
		//If it failed to complile we should be able to get the error from the data blob
		if (errorMessage != nullptr)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else	//If it failed but there was nothing in the error blob, then that means the file could not be located
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}
#pragma endregion compiling shaders

	hResult = device->CreateVertexShader(pVS->GetBufferPointer(), pVS->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(hResult))
	{
		return false;
	}
	hResult = device->CreatePixelShader(pPS->GetBufferPointer(), pPS->GetBufferSize(), nullptr, &m_pixelShader);
	if (FAILED(hResult))
	{
		return false;
	}

	hResult = device->CreateInputLayout(inputDescColor, ARRAYSIZE(inputDescColor), pVS->GetBufferPointer(), pVS->GetBufferSize(), &m_layout);
	if (FAILED(hResult))
	{
		return false;
	}

	pVS->Release();
	pVS = nullptr;
	pPS->Release();
	pPS = nullptr;

	//Setup the constant buffer for the vertices
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(Vertex);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	hResult = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(hResult))
	{
		return false;
	}

	return true;
}

void ShaderHandler::FreeMemory()
{
	//Release the matrix constant buffers
	if (this->m_vertexShader != nullptr)
	{
		m_vertexShader->Release();
		m_vertexShader = NULL;
	}

	if (this->m_pixelShader != nullptr)
	{
		m_pixelShader->Release();
		m_pixelShader = NULL;
	}

	if (this->m_layout != nullptr)
	{
		m_layout->Release();
		m_layout = NULL;
	}

	if (this->m_matrixBuffer != nullptr)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = NULL;
	}

	return;
}

void ShaderHandler::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool ShaderHandler::SetShaderParameters(ID3D11DeviceContext * deviceContext, MatrixBufferStruct matrices)	//Allows for easier update of shader values / constant buffer values
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferStruct* dataPtr = NULL;
	unsigned int bufferNumber = 0;
	
	//Transpose the matrices to prepare them for the shader (direct11 requires it?)
	matrices.world = matrices.world.Transpose();
	matrices.view = matrices.view.Transpose();
	matrices.projection = matrices.projection.Transpose();

	//Lock the m_matrix
	result = deviceContext->Map(this->m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	//Get a pointer to the data
	dataPtr = (MatrixBufferStruct*)mappedResource.pData;

	//Now we copy the matrices into the mapped data
	dataPtr->world = matrices.world;
	dataPtr->view = matrices.view;
	dataPtr->projection = matrices.projection;

	//Unlock/unmap the constant buffer
	deviceContext->Unmap(this->m_matrixBuffer, 0);

	//set the position of the constant buffer in the vertex shader
	bufferNumber = 0;

	//Set the constant buffer in the vertex shader with the updated values
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &this->m_matrixBuffer);

	return true;
}

void ShaderHandler::RenderShader(ID3D11DeviceContext * deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(this->m_layout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(this->m_pixelShader, NULL, 0);

	//Render the content
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}