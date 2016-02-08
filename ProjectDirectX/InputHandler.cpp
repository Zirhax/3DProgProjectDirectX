#include "InputHandler.h"



InputHandler::InputHandler()
{
	this->m_directInput = NULL;
	this->m_keyboard = NULL;
	this->m_mouse = NULL;
}

InputHandler::InputHandler(const InputHandler & input)
{
}


InputHandler::~InputHandler()
{
}

bool InputHandler::Initialize(HINSTANCE hInstance, HWND hwnd, int width, int height)
{
	HRESULT result;
	this->m_screenWidth = width;
	this->m_screenHeight = height;
	
	this->m_mouseX = 0;
	this->m_mouseY = 0;



	return false;
}

void InputHandler::Shutdown()
{
}

bool InputHandler::Frame()
{
	return false;
}

bool InputHandler::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}

void InputHandler::GetMouse(int & x, int & y)
{
}

bool InputHandler::ReadKeyboard()
{
	return false;
}

bool InputHandler::ReadMouse()
{
	return false;
}

void InputHandler::ProcessInput()
{
}
