#ifndef _OBJECTFACTORY_H_
#define _OBJECTFACTORY_H_

#include "StructLibrary.h"
#include "D3Object.h"
#include "TextureHandler.h"

class ObjectFactory
{
public:
	ObjectFactory();
	virtual ~ObjectFactory();
	bool CreateObject(D3Object* storeIn, char* fileName);

};

#endif