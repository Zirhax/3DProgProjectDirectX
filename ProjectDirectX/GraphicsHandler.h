#ifndef _GRAPHICSHANDLER_H_
#define _GRAPHICSHANDER_H_

#include  "d3dclass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class GraphicsHandler
{
private:
	D3DClass* m_Direct3D;
	bool Render();
public:
	GraphicsHandler();
	GraphicsHandler(const GraphicsHandler& other);
	~GraphicsHandler();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
	void ShutDown();
	bool Frame();
};

#endif