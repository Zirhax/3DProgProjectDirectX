#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

//Specify the libraries to link when using this object module.
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include "SimpleMath.h"
#include "StructLibrary.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
class D3DClass
{
private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;

	Matrix m_projectionMatrix;
	Matrix m_worldMatrix;
	Matrix m_orthoMatrix;
public:
	D3DClass();
	D3DClass(const D3DClass& other);
	virtual ~D3DClass();

	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
	void ShutDown();

	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();
	
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(Matrix& projectionMatrix);
	void GetWorldMatrix(Matrix& worldMatrix);
	void GetOrthoMatrix(Matrix& orthoMatrix);

	void GetVideoCardInfo(char* cardName, int& memory);
};

#endif