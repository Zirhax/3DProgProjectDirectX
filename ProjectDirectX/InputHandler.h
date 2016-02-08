#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

// PRE-PROCESSING DIRECTIVES 
#define DIRECTINPUT_VERSION 0x0800
// LINKING
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputHandler
{
private:
	//Interfaces to DirectInput version 8.0
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;	//The keyboard
	IDirectInputDevice8* m_mouse;		//The mouse
	
	//Contains ths currect state of the keyboard and the mouse.
	unsigned char m_keys[256];
	DIMOUSESTATE m_mouseState;
	int m_screenWidth;
	int m_screenHeight;
	int m_mouseX;
	int m_mouseY;
public:
	InputHandler();
	InputHandler(const InputHandler& input);
	~InputHandler();

	void Initialize();

	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	
	bool IsKeyDown(unsigned int key);
};

#endif