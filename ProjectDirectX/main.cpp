#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	System* system = NULL;
	bool result = false;

	//Create the system object.
	system = new System();
	if (!system)
	{
		return 0;
	}

	//Initialize and run the system object.
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}

	//Shutdown and release the system object
	system->ShutDown();
	delete system;
	system = NULL;

	return 0;
}