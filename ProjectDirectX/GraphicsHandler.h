#ifndef _GRAPHICSHANDLER_H_
#define _GRAPHICSHANDER_H_

#include "d3dclass.h"
#include "Camera.h"
#include "D2Object.h"
#include "D3Object.h"
#include "TextureHandler.h"
#include "InputHandler.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
const Vector3 UP = { 0, 0, 1 };
const Vector3 DOWN = { 0, 0, -1 };
const Vector3 LEFT = { 0, -1, 0 };
const Vector3 RIGHT = { 0, 1, 0 };


class GraphicsHandler
{
private:
	D3DClass* m_Direct3D;
	bool Render();
	Camera* m_Camera;
	D3Object* m_Model;
	TextureHandler* m_TextureShader;
	float rotation;
	//ShaderHandler* m_shaderHandler;
public:
	GraphicsHandler();
	GraphicsHandler(const GraphicsHandler& other);
	~GraphicsHandler();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void ShutDown();
	bool Frame(float dT);

	bool UpdateInput(InputHandler* inputObj, float dT);
};

#endif