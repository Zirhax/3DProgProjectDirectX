#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include "StructLibrary.h"
#include "D3Object.h"
#include "TextureHandler.h"
#include "SimpleMath.h"
#include "StructLibrary.h"
#include "TextureObject.h"
#include <fstream>

#include <string>
#include <vector>
#include <sstream>

class ObjectFactory
{
public:
	ObjectFactory();
	virtual ~ObjectFactory();


	vector<D3Object*> CreateFromFile(char* fileName, FactoryObjectFormat objectFormat);
	void CreateFromFile(char* fileName, FactoryObjectFormat objectFormat, vector<D3Object*> &storeIn);
	void CreateObjLH(char* fileName, vector<D3Object*> &storeIn);
	void CreateObjRH(char* fileName, vector<D3Object*> &storeIn);
	bool CreateObject(D3Object* storeIn, char* fileName, FactoryObjectFormat objectFormat);
	bool ReadOBJ(D3Object* storeIn, char* fileName);
};

#endif